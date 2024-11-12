// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:inductance;
export import quantify.core;

import :electric_current;
import :magnetic_flux;

export namespace quantify {
  DERIVED_SCALE(inductance, frac<magnetic_flux::scale, electric_current::scale>) {
    METRIC_SCALE(henries, "H", 1, 1)
  }
}
