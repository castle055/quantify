// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:light_intensity;
export import quantify.core;

export namespace quantify {
  SCALE(light_intensity) {
    METRIC_SCALE(candela, "cd", 1, 1)
  }
}
