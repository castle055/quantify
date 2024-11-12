// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:force;
export import quantify.core;

import :mass;
import :distance;
import :time;

export namespace quantify {
  DERIVED_SCALE(force, frac<mul<mass::scale, distance::scale>, mul<time::scale, time::scale>>) {
    UNIT(newtons, "N", 1, 1);
  }
}
