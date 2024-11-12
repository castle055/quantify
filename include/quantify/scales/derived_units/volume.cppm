// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:volume;
export import quantify.core;

import :distance;

export namespace quantify {
  DERIVED_SCALE(volume, mul<distance::scale, distance::scale, distance::scale>) {
    METRIC_SCALE(liters, "L", 1, 1)
  }
}
