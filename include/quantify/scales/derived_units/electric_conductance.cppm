// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:electric_conductance;
export import quantify.core;

import :electric_resistance;

export namespace quantify {
  DERIVED_SCALE(electric_conductance, frac<no_scale, electric_resistance::scale>) {
    METRIC_SCALE(siemens, "S", 1, 1)
  }
}
