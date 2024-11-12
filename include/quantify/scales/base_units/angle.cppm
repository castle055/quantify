// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:angle;
export import quantify.core;

export namespace quantify {
  SCALE(angle) {
    UNIT(degrees, "deg", 1,1)
    UNIT(radians, "rad", 180*10000000000000000,31415926535893238)
  }
}
