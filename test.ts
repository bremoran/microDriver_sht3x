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
// tests go here; this will not be compiled when this package is used as an extension.

basic.forever(() => {
    sht3xDriver.update(sht3xDriver.sht3xAddr.sht3xAddrA0);
    let rh = sht3xDriver.getHumidity();
    let tmp = sht3xDriver.getTemperature();
    serial.writeLine("%RH: " + rh);
    serial.writeLine("TMP: " + tmp);
    basic.pause(1000);
})