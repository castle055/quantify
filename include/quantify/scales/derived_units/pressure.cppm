// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:pressure;
export import quantify.core;

import :mass;
import :distance;
import :time;
import :force;

export namespace quantify {
  DERIVED_SCALE(pressure, frac<force::scale, mul<distance::scale, distance::scale>>) {
    METRIC_SCALE(pascals, "Pa", 1, 1);
  }
}
