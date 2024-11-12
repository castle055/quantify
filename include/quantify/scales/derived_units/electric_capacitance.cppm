// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:electric_capacitance;
export import quantify.core;

import :emf;
import :electric_charge;

export namespace quantify {
  DERIVED_SCALE(electric_capacitance, frac<electric_charge::scale, emf::scale>) {
    METRIC_SCALE(farads, "F", 1, 1)
  }
}
