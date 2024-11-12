// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:mass;
export import quantify.core;

export namespace quantify {
  SCALE(mass) {
    METRIC_SCALE(grams, "g", 1, 1000)
    UNIT(ton, "T", 1000, 1)
  }
}
