// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:electric_charge;
export import quantify.core;

import :electric_current;
import :time;

export namespace quantify {
  DERIVED_SCALE(electric_charge, mul<electric_current::scale, time::scale>) {
    METRIC_SCALE(coulombs, "C", 1, 1)
  }
}
