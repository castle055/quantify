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
export module quantify.scales:force;
export import quantify.core;

import :mass;
import :distance;
import :time;

export namespace quantify {
  DERIVED_SCALE(force, frac<mul<mass::scale, distance::scale>, mul<time::scale, time::scale>>) {
    UNIT(newtons, "N", 1, 1);
  }
}
