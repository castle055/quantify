// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:power;
export import quantify.core;

import :energy;
import :time;

export namespace quantify {
  DERIVED_SCALE(power, frac<energy::scale, time::scale>) {
    METRIC_SCALE(watts, "W", 1, 1)
  }
}
