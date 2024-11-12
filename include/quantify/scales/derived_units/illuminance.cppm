// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:illuminance;
export import quantify.core;

import :luminous_flux;
import :distance;

export namespace quantify {
  DERIVED_SCALE(illuminance, frac<luminous_flux::scale, mul<distance::scale, distance::scale>>) {
    METRIC_SCALE(lux, "lx", 1, 1)
  }
}
