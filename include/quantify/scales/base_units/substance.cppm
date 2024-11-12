// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:substance;
export import quantify.core;

export namespace quantify {
  SCALE(substance) {
    METRIC_SCALE(mole, "mol", 1, 1)
  }
}
