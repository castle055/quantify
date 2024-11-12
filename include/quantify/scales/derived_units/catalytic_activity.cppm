// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:catalytic_activity;
export import quantify.core;

import :substance;
import :time;

export namespace quantify {
  DERIVED_SCALE(catalytic_activity, frac<substance::scale, time::scale>) {
    METRIC_SCALE(katals, "kat", 1, 1)
  }
}
