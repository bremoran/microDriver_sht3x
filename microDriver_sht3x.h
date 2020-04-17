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

#ifndef MICROBITSHT31_H
#define MICROBITSHT31_H

#include <stddef.h>
#include "pxt.h"

using namespace pxt;

namespace sht3xDriver {
    typedef enum {
        SHT3x_A0 = 0x44 << 1,
        SHT3x_A1 = 0x45 << 1,
    } SHT3x_Address;
    //%
    int update(int8_t addr);
    //%
    float getHumidity();
    //%
    float getTemperature();
}

#endif // MICROBITSHT31_H