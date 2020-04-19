// ----------------------------------------------------------------------------
// Copyright 2020 Brendan Moran
//
// SPDX-License-Identifier: MIT
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
// ----------------------------------------------------------------------------

#include <stdint.h>
#include "microDriver_sht3x.h"
using namespace pxt;

/**
 * A micro:bit Makecode driver for SHT3x devices
 *
 * Due to size limitations, many micro:bit drivers do not implement floating
 * point numbers. Frequently, this leads to a loss of precision. This driver
 * takes a different approach. Recognising that the Makecode interpreter
 * already has floating point support, this driver returns raw values and
 * converts them to floating piont in a typescript shim to ensure no loss
 * of precision.
 */
namespace sht3xDriver {
    static uint16_t tempRaw;
    static uint16_t humRaw;
    static uint16_t lastStatus;

    /**
     * @brief Perform a 1-shot read operation on the SHT3x
     * 
     * Sends command to addr, then reads length bytes into buffer.
     * Sets the lastStatus variable on failure.
     * 
     * @param addr The i2c address of the SHT3x.
     * @param command The command to send to the SHT3x
     * @param buffer The output buffer to write bytes into
     * @param length The number of bytes to write into buffer
     * @retval 0 for success
     * @retval 1 for failure on i2c write
     * @retval 2 for failure on i2c read
     */
    static int readCommand(int8_t addr, uint16_t command, uint8_t *buffer, size_t length)
    {
        int8_t cmdBuffer [2];
        cmdBuffer[0] = (command >> 8) & 0xff;
        cmdBuffer[1] = command & 0xff;
        MicroBitI2C i2c(I2C_SDA0, I2C_SCL0);
        int rc = MICROBIT_OK;
        if (MICROBIT_OK != (rc = i2c.write(addr, (const char *)cmdBuffer, 2))) {
            return 1;
        }
        fiber_sleep(70);
        for (size_t i = 0; i < 4; i++) {
            if (MICROBIT_OK == (rc = i2c.read(addr, (char *)buffer, length))) {
                return rc;
            }
            fiber_sleep(30);
        }
        return 2;
    }

    /**
     * @brief A compact, but slow slow implementation of CRC8 for SHT3x
     * 
     * This implements a classic MSB-first bit-shifting CRC, using polynomial
     * 0x31 and initial value 0xFF, as specified in the SHT3x datasheet.
     * 
     * @param buf the data to CRC
     * @param len the length of the data
     * @return the CRC8 of the supplied data
     */
    uint8_t crcSlow(uint8_t *buf, size_t len) {
        const uint8_t generatorPolynomial = 0x31;
        uint8_t remainderPolynomial = 0xFF;
        for (size_t i = 0; i < len; i++ ) {
            remainderPolynomial = remainderPolynomial ^ buf[i];
            for (size_t j = 8; j ; j--) {
                if (remainderPolynomial & 0x80) {
                    remainderPolynomial = (remainderPolynomial << 1) ^ generatorPolynomial;
                } else {
                    remainderPolynomial = (remainderPolynomial << 1);
                }
            }
        }
        return remainderPolynomial;
    }

    /**
     * @brief a wrapper for crcSlow
     * 
     * This function uses crcSlow, then compares the result to an expected
     * value.
     * 
     * @param data the data to verify
     * @param len the length of the data to verify
     * @param crcExpected the CRC that data should match
     * 
     * @retval MICROBIT_I2C_ERROR if there is a mismatch
     * @retval MICROBIT_OK on success
     */
    int verifyChecksum (uint8_t *data, size_t len, uint8_t crcExpected) {
        uint8_t crcActual = crcSlow(data, len);
        if (crcActual != crcExpected) {
            return MICROBIT_I2C_ERROR;
        }
        return MICROBIT_OK;
    }

    /**
     * @brief Perform a reading of a SHT3x sensor
     * 
     * This function initiates an I2C reading of a SHT3x sensor. It uses clock
     * stretching to wait until the SHT3x finishes a read. The SHT3x is
     * instructed to use a one-shot high precision measurement. A CRC is
     * calculated for each measurement.
     * 
     * The temperature and humidity data is stored in the internal raw
     * variables. It can be queried with humidityRaw and temperatureRaw.
     * 
     * The internal status variable is also updated by this function. It can
     * be queried with status.
     * 
     * @param addr The i2c address of the SHT3x.
     * 
     * status is set to 3 if temperature checksum is invalid
     * status is set to 4 if humidity checksum is invalid
     */ 
    void update(int8_t addr) {
        uint8_t dataBuffer[6];
        lastStatus = 0;
        int rc = readCommand(addr, 0x2C06, dataBuffer, 6);
        if (rc != MICROBIT_OK) {
        }
        else if (MICROBIT_OK != verifyChecksum(dataBuffer, 2, dataBuffer[2])) {
            lastStatus = 3;
        }
        else if (MICROBIT_OK != verifyChecksum(&dataBuffer[3], 2, dataBuffer[5])) {
            lastStatus = 4;
        }
        else {
            tempRaw = dataBuffer[0] << 8 | dataBuffer[1];
            humRaw = dataBuffer[3] << 8 | dataBuffer[4];
        }
    }

    /**
     * @brief report the status of the last update
     * 
     * @retval 0 success
     * @retval 1, the I2C write failed
     * @retval 2, the I2C read failed
     * @retval 3, the temperature checksum was invalid
     * @retval 4, the humidity checksum was invalid
     */
    int status() {
        return lastStatus;
    }

    /**
     * @brief report the raw humidity of the last update
     * 
     * @return a value between 0x0000 (no humidity) and 0xFFFF (100% humidity)
     */
    unsigned humidityRaw() {
        // unsigned H = 10000 * (unsigned)humRaw / 0xFFFF;
        return humRaw;
    }

    /**
     * @brief report the raw temperature of the last update
     * 
     * @return a value between 0 (-45 C) and 0xFFFF (130 C)
     */
    int temperatureRaw() {
        // int T =  (17500 * ((int) tempRaw) - (4500*0xFFFFL))/0xFFFFL;
        return tempRaw;
    }
}