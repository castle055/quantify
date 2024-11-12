// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

export module quantify.ratio;

export
namespace quantify {
  template<typename T, auto Num, auto Den>
  struct ratio {
    static constexpr T numerator   = Num;
    static constexpr T denominator = Den;
  };
}
