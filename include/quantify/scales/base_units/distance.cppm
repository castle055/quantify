// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

module;
#include "quantify/unit_macros.h"
export module quantify.scales:distance;
export import quantify.core;

export namespace quantify {
  SCALE(distance) {
    UNIT(meters, "m", 1,1)

    //! Metric
    UNIT(decimeter, "dm", 1,10)
    UNIT(centimeter, "cm", 1,100)
    UNIT(millimeter, "mm", 1,1000)
    UNIT(micrometer, "um", 1,1000000)
    UNIT(nanometer, "nm", 1,1000000000)

    UNIT(decameters, "Dm", 10,1)
    UNIT(hectometers, "hm", 100,1)
    UNIT(kilometers, "km", 1000, 1)
    UNIT(megameters, "Mm", 1000000, 1)

    //! Imperial
    UNIT(inches, "in", 127,5000)
    UNIT(feet, "ft", 381,1250)
    UNIT(yard, "yd", 1143,1250)
    UNIT(mile, "mi", 201168,125)
    UNIT(league, "lea", 3*mile::factor<T>::numerator,1250)

    UNIT(fathom, "ftm", 463,250)
    UNIT(nautical_mile, "nmi", 1852,1)
  }
}
