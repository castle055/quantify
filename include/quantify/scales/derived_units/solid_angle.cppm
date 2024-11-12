// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:solid_angle;
export import quantify.core;

import :angle;

export namespace quantify {
  DERIVED_SCALE(solid_angle, mul<angle::scale, angle::scale>) {
    METRIC_SCALE(steradian, "sr", 1, 1)
  }
}
