// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:time;
export import quantify.core;

export namespace quantify {
  SCALE(time) {
    UNIT(seconds, "s", 1,1)

    UNIT(milliseconds, "ms", 1,1000)
    UNIT(microseconds, "us", 1,1000000)
    UNIT(nanoseconds, "ns", 1,1000000000)

    UNIT(minutes, "min", 60,1)
    UNIT(hours, "hours", minutes::factor<T>::numerator*60,1)
    UNIT(days, "days", hours::factor<T>::numerator*24,1)
    UNIT(months, "months", days::factor<T>::numerator*30,1)
    UNIT(years, "years", days::factor<T>::numerator*365,1)
    UNIT(decades, "decades", years::factor<T>::numerator*10,1)
    UNIT(centuries, "centuries", decades::factor<T>::numerator*10,1)
    UNIT(millennia, "millennia", centuries::factor<T>::numerator*10,1)
  }
}
