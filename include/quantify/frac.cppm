// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

//
// Created by castle on 5/11/24.
//
module;
#include <quantify/unit_macros.h>
export module quantify.core:frac;
import std;
import packtl;
export import quantify.ratio;

export namespace quantify {
  template<typename Numerator, typename Denominator>
  struct frac {
    UNIT_SYMBOL("(" + Numerator::symbol() + ")/(" + Denominator::symbol() + ")")
  };

  template<typename Numerator, typename Denominator>
  requires requires {
    typename Numerator::scale;
    typename Denominator::scale;
  }
  struct frac<Numerator, Denominator> {
    using scale  = frac<typename Numerator::scale, typename Denominator::scale>;

    template<typename T>
    using factor = ratio<
      T,
      (long)(Numerator::template factor<T>::numerator * Denominator::template factor<T>::denominator),
      (long)(Numerator::template factor<T>::denominator * Denominator::template factor<T>::numerator)
    >;

    UNIT_SYMBOL("(" + Numerator::symbol() + ")/(" + Denominator::symbol() + ")")
  };
}
