// ----------------------------------------------------------------------------
// Copyright 2020 Brendan Moran
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#include <stdint.h>
#include "microDriver_sht3x.h"
using namespace pxt;

namespace sht3xDriver {
    static uint16_t temp_raw;
    static uint16_t hum_raw;

    int readCommand(int8_t addr, uint16_t command, uint8_t *buffer, size_t length)
    {
        int8_t cmdBuffer [2];
        cmdBuffer[0] = (command >> 8) & 0xff;
        cmdBuffer[1] = command & 0xff;
        MicroBitI2C i2c(I2C_SDA0, I2C_SCL0);
        int rc = MICROBIT_OK;
        if (MICROBIT_OK != (rc = i2c.write(addr, (const char *)cmdBuffer, 2))) {
            return rc;
        }
        fiber_sleep(70);
        for (size_t i = 0; i < 4; i++) {
            if (MICROBIT_OK == (rc = i2c.read(addr, (char *)buffer, length))) {
                return rc;
            }
            fiber_sleep(30);
        }
        return rc;
    }

    uint8_t crcSlow(uint8_t *buf, size_t len) {
        const uint8_t generatorPolynomial = 0x31;
        uint8_t remainderPolynomial = 0xFF;
        // A popular variant complements remainderPolynomial here; see § Preset to −1 below
        for (size_t i = 0; i < len; i++ ) {
            remainderPolynomial = remainderPolynomial ^ buf[i];
            for (size_t j = 8; j ; j--) {    // Assuming 8 bits per byte
                if (remainderPolynomial & 0x80) {
                    remainderPolynomial = (remainderPolynomial << 1) ^ generatorPolynomial;
                } else {
                    remainderPolynomial = (remainderPolynomial << 1);
                }
            }
        }
        // A popular variant complements remainderPolynomial here; see § Post-invert below
        return remainderPolynomial;
    }

    int verify_checksum (uint8_t *data, size_t len, uint8_t crcActual) {
        uint8_t crcExpected = crcSlow(data, len);
        if (crcActual != crcExpected) {
            return MICROBIT_I2C_ERROR;
        }
        return MICROBIT_OK;
    }

    int update(int8_t addr) {
        uint8_t dataBuffer[6];
        int rc = readCommand(addr, 0x2C06, dataBuffer, 6);
        if (rc != MICROBIT_OK) {
            return rc;
        }
        if (MICROBIT_OK != (rc = verify_checksum(dataBuffer, 2, dataBuffer[2]))) {
            return rc;
        }
        if (MICROBIT_OK != (rc = verify_checksum(&dataBuffer[3], 2, dataBuffer[5]))) {
           return rc;
        }
        temp_raw = dataBuffer[0] << 8 | dataBuffer[1];
        hum_raw = dataBuffer[3] << 8 | dataBuffer[4];

        return rc;
    }
    float getHumidity() {
        float H = 100 * (float)hum_raw / 0xFFFF;
        return H;
    }
    float getTemperature() {
        float T =  (175 * ((float) temp_raw) - (45*0xFFFFL))/0xFFFFL;
        float absT = T > 0 ? T : -T;
        return T;
    }

}