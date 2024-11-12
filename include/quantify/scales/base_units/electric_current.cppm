// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:electric_current;
export import quantify.core;

export namespace quantify {
  SCALE(electric_current) {
    METRIC_SCALE(ampere, "A", 1, 1)
  }
}
