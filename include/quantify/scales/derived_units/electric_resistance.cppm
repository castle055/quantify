// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:electric_resistance;
export import quantify.core;

import :emf;
import :electric_current;

export namespace quantify {
  DERIVED_SCALE(electric_resistance, frac<emf::scale, electric_current::scale>) {
    METRIC_SCALE(ohms, "ohm", 1, 1)
  }
}
