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
//% color=#5c7ef5 weight=25 icon="\uf043" block="SHT3x Sensor"
namespace sht3xDriver {
    export enum Sht3xAddr {
        //% block="A0"
        sht3xAddrA0 = 0x44<<1,
        //% block="A1"
        sht3xAddrA1 = 0x45<<1,
    }

    /**
     * Update a SHT3x sensor reading
     */
    //% shim=sht3xDriver::update
    //% blockId="SHT3xDriver_update"
    //% block="SHT3xUpdate %addr"
    export function update(addr: Sht3xAddr){
        // Dummy implementation for the simulator.
        console.log("Read SHT3x sensor");
    }
    
    /**
     * Report the status of the last update
     * 
     * @retval 0 success
     * @retval 1, the I2C write failed
     * @retval 2, the I2C read failed
     * @retval 3, the temperature checksum was invalid
     * @retval 4, the humidity checksum was invalid
     */
    //% shim=sht3xDriver::status
    //% blockId="SHT3xDriver_status"
    //% block="SHT3xStatus"
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
     * Report Relative Humidity from the SHT3x Sensor.
     * Returns a number describing the relative humidity in percentage % relative
     * humidity
     */
    //% blockId="SHT3xDriver_humidity"
    //% block="SHT3xHumidity"
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
     * Report Temperature in degrees celcius from the SHT3x sensor.
     * Returns a number describing the ambient temperature in degrees celcius
     */
    //% blockId="SHT3xDriver_temperature"
    //% block="SHT3xTemperature"
    export function temperature(): number{
        return 175*temperatureRaw()/0xFFFF - 45;
    }
}