// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:luminous_flux;
export import quantify.core;

import :light_intensity;
import :solid_angle;

export namespace quantify {
  DERIVED_SCALE(luminous_flux, mul<light_intensity::scale, solid_angle::scale>) {
    METRIC_SCALE(lumen, "lm", 1, 1)
  }
}
