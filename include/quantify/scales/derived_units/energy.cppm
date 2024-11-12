// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:energy;
export import quantify.core;

import :force;
import :distance;

export namespace quantify {
  DERIVED_SCALE(energy, mul<force::scale, distance::scale>) {
    METRIC_SCALE(joule, "J", 1, 1)
  }
}
