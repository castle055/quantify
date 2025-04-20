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
#include "quantify/unit_macros.h"

export module quantify.core:preface;
export import std;
export import packtl;
export import quantify.ratio;

namespace quantify {
  export struct no_scale {

  };
  export struct no_unit {
    using scale = no_scale;
    using reduce = no_unit;

    template<typename T>
    using factor = ratio<T, 1, 1>;

    UNIT_SYMBOL("(no unit)")
  };

  export template<typename U_FROM, typename U_TO, typename T>
  struct unit_conversion_t {
  };

  export template<typename S_FROM, typename S_TO>
  struct scale_conversion_t;

  export {
    template <typename Expr>
    struct reduce_impl {
      using type = Expr;
    };

    template <typename Expr>
    using reduce = typename reduce_impl<Expr>::type;
  }

  export {
    template <typename...>
    struct mul;

    template <typename N, typename D>
    struct frac;

    template <typename ...>
    struct is_mul: std::false_type {};

    template <typename ...Args>
    struct is_mul<mul<Args...>>: std::true_type {};

    template <typename M>
    constexpr bool is_mul_v = is_mul<M>::value;

    template <typename ...>
    struct is_frac: std::false_type {};

    template <typename ...Args>
    struct is_frac<frac<Args...>>: std::true_type {};

    template <typename F>
    constexpr bool is_frac_v = is_frac<F>::value;

    template <typename S>
    concept has_scale = requires {
      typename S::scale;
    };

    template <typename S>
    constexpr bool has_scale_v = has_scale<S>;

    template <typename Mul, typename CancelProduct>
    using cancel_out = typename packtl::take_one_out<CancelProduct, Mul>::type;

    template <typename...>
    struct cancel_out_many { };

    template <typename Mul, typename CP>
    struct cancel_out_many<Mul, CP> {
      using type = cancel_out<Mul, CP>;
    };

    template <typename Mul, typename CP1, typename... CancelProducts>
    struct cancel_out_many<Mul, CP1, CancelProducts...> {
    private:
      using cancelled      = typename packtl::take_one_out<CP1, Mul>::type;
      using cancelled_many = std::conditional_t<
        (sizeof...(CancelProducts) > 1),
        cancel_out_many<cancelled, CancelProducts...>,
        packtl::take_one_out<typename packtl::get_first<CancelProducts...>::type, cancelled>>;

      using result = std::conditional_t<
        sizeof...(CancelProducts) == 0,
        cancelled,
        typename cancelled_many::type>;

    public:
      using type = result;
    };

    template <typename Mul, template <typename...> typename Pack, typename... CancelProducts>
    struct cancel_out_many<Mul, Pack<CancelProducts...>> {
      using type = typename cancel_out_many<Mul, CancelProducts...>::type;
    };

    template <typename M>
    struct normalize {
      using type = M;
    };

    template <typename M>
    using normalize_t = typename normalize<M>::type;


    template <typename M, typename...>
    struct normalize_impl {
      using type = M;
    };

    template <typename M>
    using normalize_impl_t = typename normalize_impl<M>::type;

    template <typename Num, typename Den, typename... Ps>
    struct normalize_impl<mul<frac<Num, Den>, Ps...>> {
      using type = frac<normalize_t<mul<Ps..., Num>>, Den>;
    };

    template <typename P1, typename... Ps>
      requires (!is_frac_v<P1> && (is_frac_v<Ps> || ...))
    struct normalize_impl<mul<P1, Ps...>> {
      using type = normalize_impl_t<mul<Ps..., P1>>;
    };

    
    template <typename... Ps>
    struct normalize<mul<Ps...>> {
      using type = normalize_impl_t<typename packtl::flatten<mul<Ps...>>::type>;
    };
  }
}
