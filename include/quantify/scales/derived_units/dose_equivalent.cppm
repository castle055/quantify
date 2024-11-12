// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:dose_equivalent;
export import quantify.core;

import :energy;
import :mass;

export namespace quantify {
  DERIVED_SCALE(dose_equivalent, mul<energy::scale, mass::scale>) {
    METRIC_SCALE(sieverts, "Sv", 1, 1)
  }
}
