// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:radionuclide_activity;
export import quantify.core;

import :time;

export namespace quantify {
  DERIVED_SCALE(radionuclide_activity, frac<no_scale, time::scale>) {
    METRIC_SCALE(becquerels, "Bq", 1, 1)
  }
}
