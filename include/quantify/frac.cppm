// Copyright (c) 2024-2025, Víctor Castillo Agüero.
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
