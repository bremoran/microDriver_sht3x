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

/** 
 * This driver uses the convention of returning numbers in raw form so
 * that no floating point processing is needed. The typescript floating point
 * handling is overhead that is already included, so numbers are divided by
 * converted to floating point after being handed to the typescript shim.
 */

/**
 * The SHT3x Driver provides access to the functionality of the SHT30, SHT31 
 * and SHT35 sensors
 */
//% color=#5c7ef5 weight=25 icon="\uf043" block="sht3x Sensor"
namespace sht3xDriver {
    export enum sht3xAddr {
        //% block="A0"
        sht3xAddrA0 = 0x44<<1,
        //% block="A1"
        sht3xAddrA1 = 0x45<<1,
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
    //% shim=sht3xDriver::update
    //% blockId="SHT3xDriver_update"
    //% block="updateSHT3x %addr"
    export function update(addr: sht3xAddr){
        // Dummy implementation for the simulator.
        console.log("Read SHT3x sensor");
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
    //% shim=sht3xDriver::status
    //% blockId="SHT3xDriver_status"
    //% block="sht3x reading status"
    export function status(): number {
        // Dummy implementation for the simulator.
        console.log("Simulate: Status from SHT3x sensor:");
        return 0
    }

    /**
     * @brief report the raw humidity of the last update
     * 
     * @return a value between 0x0000 (no humidity) and 0xFFFF (100% humidity)
     */
    //% shim=sht3xDriver::humidityRaw
    function humidityRaw(): number{
        // Dummy implementation for the simulator.
        console.log("Simulate: Read Humidity from SHT3x sensor: 5000");
        return 0xffff/2;
    }
    /**
     * Read Relative Humidity from the SHT3x Sensor.
     * Returns a number describing the relative humidity in percentage % relative
     * humidity
     */
    //% blockId="SHT3xDriver_read_humidity"
    //% block="read humidty"
    export function humidity(): number{
        return 100*humidityRaw()/0xffff;
    }

    /**
     * @brief report the raw temperature of the last update
     * 
     * @return a value between 0 (-45 C) and 0xFFFF (130 C)
     */
    //% shim=sht3xDriver::temperatureRaw
    function temperatureRaw(): number{
        // Dummy implementation for the simulator.
        console.log("Simulate: Read Temperature from SHT3x sensor: 3000");
        return (30+45) * 0xFFFF / 175;
    }
    /**
     * Read Temperature in degrees celcius from the SHT3x sensor.
     * Returns a number describing the ambient temperature in degrees celcius
     */
    //% blockId="SHT3xDriver_read_temperature"
    //% block="read temperature"
    export function temperature(): number{
        return 175*temperatureRaw()/0xFFFF - 45;
    }
}