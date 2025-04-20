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

export module quantify.scales:electric_conductance;
import quantify.core;

import :electric_resistance;

export namespace quantify {
  //! @addtogroup derived_units Derived scales
  //! @{
  DERIVED_SCALE(electric_conductance, frac<no_scale, electric_resistance::scale>) {
    METRIC_UNIT(siemens, "S", 1, 1);
  }
  //! @}
}
