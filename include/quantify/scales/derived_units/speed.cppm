// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:speed;
export import quantify.core;

import :distance;
import :time;

export namespace quantify {
  namespace speed {
    using scale = frac<distance::scale, time::scale>;
    template<typename Q> concept quantity = Quantity<Q, scale>;

    struct m_s: frac<distance::meters, time::seconds> {};
  }
}
