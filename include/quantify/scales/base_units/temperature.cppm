// Copyright (c) 2024-2025, Víctor Castillo Agüero.
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

module;
#include "quantify/unit_macros.h"
export module quantify.scales:temperature;
export import quantify.core;

export namespace quantify {
  namespace temperature {
    namespace scales {
      SCALE(kelvin) {}
      SCALE(celsius) {}
      SCALE(fahrenheit) {}
    }

    UNIT_IN_SCALE(scales::kelvin::scale, kelvin, "K", 1, 1)

    UNIT_IN_SCALE(scales::celsius::scale, celsius, "C", 1, 1)
    UNIT_IN_SCALE(scales::celsius::scale, millicelsius, "mC", 1, 1000)

    UNIT_IN_SCALE(scales::fahrenheit::scale, fahrenheit, "F", 1, 1)
  }
}

using namespace quantify::temperature;
export
{
//@formatter:off
  SCALE_CONVERSION(scales::kelvin::scale, scales::celsius::scale)
    SCALE_FORWARD_CONVERSION(it - 273.15) SCALE_BACKWARD_CONVERSION(it + 273.15)

  SCALE_CONVERSION(scales::celsius::scale, scales::fahrenheit::scale)
    SCALE_FORWARD_CONVERSION((it * 9 / 5) + 32) SCALE_BACKWARD_CONVERSION((it - 32) * 5 / 9)

  SCALE_CONVERSION(scales::kelvin::scale, scales::fahrenheit::scale)
    SCALE_FORWARD_CONVERSION(((it - 273.15) * 9 / 5) + 32) SCALE_BACKWARD_CONVERSION(((it - 32) * 5 / 9) + 273.15)
//@formatter:on
}
