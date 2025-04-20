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

export module quantify.core:mul;
import std;
import :preface;
import :frac;
export import quantify.ratio;

export namespace quantify {
  template <typename... Products>
  struct mul {
    UNIT_SYMBOL(symbol_builder<Products...>::symbol())

  private:
    template <typename...>
    struct symbol_builder {
      UNIT_SYMBOL(no_unit::symbol())
    };

    template <typename P>
    struct symbol_builder<P> {
      UNIT_SYMBOL(P::symbol())
    };

    template <typename P, typename... Ps>
      requires (sizeof...(Ps) > 0)
    struct symbol_builder<P, Ps...> {
      UNIT_SYMBOL(P::symbol() + "*" + symbol_builder<Ps...>::symbol())
    };
  };

  template <typename... Products>
  requires (has_scale_v<Products> && ...)
  struct mul<Products...> {
    using scale  = mul<typename Products::scale...>;
    // using reduce = typename ts::packs::flatten<mul<typename Products::reduce...>>::type;

    template <typename T>
    using factor = ratio<
      T,
      (long)(1 * ... * Products::template factor<T>::numerator),
      (long)(1 * ... * Products::template factor<T>::denominator)
    >;

    UNIT_SYMBOL(symbol_builder<Products...>::symbol())

  private:
    template <typename...>
    struct symbol_builder {
      UNIT_SYMBOL(no_unit::symbol())
    };

    template <typename P>
    struct symbol_builder<P> {
      UNIT_SYMBOL(P::symbol())
    };

    template <typename P, typename... Ps>
      requires (sizeof...(Ps) > 0)
    struct symbol_builder<P, Ps...> {
      UNIT_SYMBOL(P::symbol() + "*" + symbol_builder<Ps...>::symbol())
    };
  };
}
