// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"

export module quantify.scales:magnetic_flux;
export import quantify.core;

import :emf;
import :time;

export namespace quantify {
  DERIVED_SCALE(magnetic_flux, mul<emf::scale, time::scale>) {
    METRIC_SCALE(webers, "Wb", 1, 1)
  }
}
