// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:emf;
export import quantify.core;

import :power;
import :electric_current;

export namespace quantify {
  DERIVED_SCALE(emf, frac<power::scale, electric_current::scale>) {
    METRIC_SCALE(volts, "V", 1, 1)
  }
}
