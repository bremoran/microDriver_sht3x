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
 * The SHT3x Driver provides access to the functionality of the SHT30, SHT31 
 * and SHT35 sensors
*/
//% color=#4c6ef5 weight=25 icon="\uf043" block="sht3x Sensor"
namespace sht3xDriver {
    export enum sht3xAddr {
        sht3xAddrA0 = 0x44<<1,
        sht3xAddrA1 = 0x45<<1,
    }

    /**
     * Update readings from the SHT3x Sensor.
    */
    //% shim=sht3xDriver::update
    //% blockId="SHT3xDriver_rupdate"
    //% block="update SHT3x readingsg"
    export function update(addr: sht3xAddr): number{
        // Dummy implementation for the simulator.
        console.log("Read SHT3x sensor");
        return 0;
    }

    /**
     * Read Relative Humidity from the SHT3x Sensor.
     * Returns a number describing the relative humidity in percentage % relative
     * humidity
    */
    //% shim=sht3xDriver::getHumidity
    //% blockId="SHT3xDriver_read_humidity"
    //% block="read humidty"
    export function getHumidity(): number{
        // Dummy implementation for the simulator.
        console.log("Simulate: Read Humidity from SHT3x sensor: 50");
        return 50.0;
    }

    /**
     * Read Temperature in degrees celcius from the SHT3x sensor.
     * Returns a number describing the ambient temperature in degrees celcius
    */
    //% shim=sht3xDriver::getTemperature
    //% blockId="SHT3xDriver_read_temperature"
    //% block="read temperature"
    export function getTemperature(): number{
        // Dummy implementation for the simulator.
        console.log("Simulate: Read Temperature from SHT3x sensor: 50");
        return 30.0;
    }
}