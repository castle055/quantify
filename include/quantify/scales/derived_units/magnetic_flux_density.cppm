// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:magnetic_flux_density;
export import quantify.core;

import :magnetic_flux;
import :distance;

export namespace quantify {
  DERIVED_SCALE(magnetic_flux_density, frac<magnetic_flux::scale, mul<distance::scale, distance::scale>>) {
    METRIC_SCALE(teslas, "T", 1, 1)
  }
}
