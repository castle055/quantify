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
export module quantify.scales:distance;
import quantify.core;

export namespace quantify {
  //! @addtogroup base_units Base scales
  //! @{
  SCALE(distance) {
    METRIC_UNIT(meter, "m", 1, 1);

    UNIT(inches, "in", 127, 5000);
    UNIT(feet, "ft", 381, 1250);
    UNIT(yard, "yd", 1143, 1250);
    UNIT(mile, "mi", 201168, 125);
    UNIT(league, "lea", 3 * mile::factor<T>::numerator, 1250);

    UNIT(fathom, "ftm", 463, 250);
    UNIT(nautical_mile, "nmi", 1852, 1);
  }
  //! @}
} // namespace quantify
