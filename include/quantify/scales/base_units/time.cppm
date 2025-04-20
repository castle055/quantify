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
export module quantify.scales:time;
import quantify.core;

export namespace quantify {
  //! @addtogroup base_units Base scales
  //! @{
  SCALE(time) {
    UNIT(seconds, "s", 1, 1);

    UNIT(milliseconds, "ms", 1, 1000);
    UNIT(microseconds, "us", 1, 1000000);
    UNIT(nanoseconds, "ns", 1, 1000000000);

    UNIT(minutes, "min", 60, 1);
    UNIT(hours, "hours", minutes::factor<T>::numerator * 60, 1);
    UNIT(days, "days", hours::factor<T>::numerator * 24, 1);
    UNIT(months, "months", days::factor<T>::numerator * 30, 1);
    UNIT(years, "years", days::factor<T>::numerator * 365, 1);
    UNIT(decades, "decades", years::factor<T>::numerator * 10, 1);
    UNIT(centuries, "centuries", decades::factor<T>::numerator * 10, 1);
    UNIT(millennia, "millennia", centuries::factor<T>::numerator * 10, 1);
  }
  //! @}
} // namespace quantify
