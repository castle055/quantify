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

//! Syntax sugar - Apply reduce
#define R(...) reduce<__VA_ARGS__>

export module quantify.core:quantity;
import std;
import :preface;
import :concepts;
export import :frac;
export import :mul;

export namespace quantify {
  template<typename U, typename T>
  struct quantity {
    using unit      = U;
    using data_type = T;

    T value { };

    T value_as_base_unit() const {
      return value * U::template factor<T>::numerator / U::template factor<T>::denominator;
    }

    template<typename U1>
      requires SameScale<U, U1>
    auto operator<=>(const quantity<U1, T>& rhl) const {
      return this->value <=> rhl.template as<U>().value;
    }

    template<typename U1>
      requires SameScale<U, U1>
    bool operator<(const quantity<U1, T>& rhl) const {
      return this->value < rhl.template as<U>().value;
    }

    template<typename U1>
      requires SameScale<U, U1>
    bool operator==(const quantity<U1, T>& rhl) const {
      return this->value == rhl.template as<U>().value;
    }

    template<typename T1>
      requires (not QuantityConcept<T1>)
    auto operator<=>(const T1& rhl) const {
      return this->value <=> rhl;
    }

    template<typename T1>
      requires (not QuantityConcept<T1>)
    bool operator<(const T1& rhl) const {
      return this->value < rhl;
    }

    template<typename T1>
      requires (not QuantityConcept<T1>)
    bool operator==(const T1& rhl) const {
      return this->value == rhl;
    }

    template<typename U1>
      requires SameScale<U, U1>
    quantity<R(frac<R(U), R(U)>), T> operator/(const quantity<U1, T> &rhl) const {
      return {this->value / rhl.template as<R(U)>().value};
    }

    template<typename U1>
      requires (!SameScale<U, U1>)
    quantity<R(frac<R(U), R(U1)>), T> operator/(const quantity<U1, T> &rhl) const {
      return {this->value / rhl.value};
    }

    template<typename T1>
      requires (not QuantityConcept<T1>)
    quantity<R(U), T> operator/(const T1& rhl) const {
      return {this->value / rhl};
    }

    template<typename U1>
      requires SameScale<U, U1>
    quantity<R(mul<R(U), R(U)>), T> operator*(const quantity<U1, T> &rhl) const {
      return {this->value * rhl.template as<R(U)>().value};
    }

    template<typename U1>
      requires (!SameScale<U, U1>)
    quantity<R(mul<R(U), R(U1)>), T> operator*(const quantity<U1, T> &rhl) const {
      return {this->value * rhl.value};
    }

    template<typename T1>
      requires (not QuantityConcept<T1>)
    quantity<R(U), T> operator*(const T1& rhl) const {
      return {this->value * rhl};
    }

    template<typename U1, typename T1>
      requires (SameScale<U, U1>)
    quantity<R(U), T1> operator+(const quantity<U1, T1> &rhl) const {
      return {this->value + rhl.template as<R(U)>().value};
    }

    template<typename U1, typename T1>
      requires (SameScale<U, U1>)
    quantity<R(U), T1>& operator+=(const quantity<U1, T1> &rhl) {
      this->value += rhl.template as<R(U)>().value;
      return *this;
    }

    template<typename U1, typename T1>
      requires (SameScale<U, U1>)
    quantity<R(U), T1> operator-(const quantity<U1, T1> &rhl) const {
      return {this->value - rhl.template as<R(U)>().value};
    }

    template<typename U1, typename T1>
      requires (SameScale<U, U1>)
    quantity<R(U), T1>& operator-=(const quantity<U1, T1> &rhl) {
      this->value -= rhl.template as<R(U)>().value;
      return *this;
    }

    quantity<U, T> operator-() const {
      return {-(this->value)};
    }

    constexpr quantity() = default;

    constexpr quantity(T value_): value(value_) {
    }

    //! Copy
    template <typename T1>
    quantity(const quantity<U,T1> &other) {
      this->value = other.value;
    }

    //! Copy
    template <typename U1, typename T1>
      requires(
        not std::same_as<R(U), R(U1)> &&
        (SameScale<U, U1> || Convertible<U, U1, T> ||
         ConvertibleScales<typename U::scale, typename U1::scale, U, U1, T>)
      )
    quantity(const quantity<U1, T1>& other) {
      this->value = other.template as<U>().value;
    }

    //! Copy
    template <typename T1>
    quantity &operator=(const quantity<U,T1> &rhl) {
      this->value = rhl.value;
      return *this;
    }

    //! Copy
    template <typename U1, typename T1>
      requires(
        not std::same_as<R(U), R(U1)> &&
        (SameScale<U, U1> || Convertible<U, U1, T> ||
         ConvertibleScales<typename U::scale, typename U1::scale, U, U1, T>)
      )
    quantity &operator=(const quantity<U1, T1> &rhl) {
      this->value = rhl.template as<U>().value;
      return *this;
    }

    //! Move
    template <typename T1>
    quantity(quantity<U,T1> &&other) noexcept {
      this->value = other.value;
    }

    //! Move
    template <typename U1, typename T1>
      requires(
        not std::same_as<R(U), R(U1)> &&
        (SameScale<U, U1> || Convertible<U, U1, T> ||
         ConvertibleScales<typename U::scale, typename U1::scale, U, U1, T>)
      )
    quantity(quantity<U1, T1>&& other) {
      this->value = other.template as<U>().value;
    }

    //! Move
    template <typename T1>
    quantity &operator=(quantity<U,T1> &&rhl) noexcept {
      this->value = rhl.value;
      return *this;
    }

    //! Move
    template <typename U1, typename T1>
      requires(
        not std::same_as<R(U), R(U1)> &&
        (SameScale<U, U1> || Convertible<U, U1, T> ||
         ConvertibleScales<typename U::scale, typename U1::scale, U, U1, T>)
      )
    quantity &operator=(quantity<U1, T1> &&rhl) {
      this->value = rhl.template as<U>().value;
      return *this;
    }


    template<typename U1>
      requires SameScale<U, U1> || Convertible<U, U1, T> || ConvertibleScales<typename U::scale, typename U1::scale, U, U1, T>
    [[nodiscard]]
    constexpr quantity<U1, T> as() const {
      if constexpr (std::is_same_v<U, U1>) {
        return *this;
      } else if constexpr (SameScale<U, U1>) {
        return quantity<U1, T> {
          this->value
          * (U1::template factor<T>::denominator
             * U::template factor<T>::numerator)
          / (U1::template factor<T>::numerator
             * U::template factor<T>::denominator)
        };
      // } else if constexpr (requires { scale_conversion_t<typename U::scale, typename U1::scale>::template forward<U, U1, T>(*this); }) {
      //   return scale_conversion_t<typename U::scale, typename U1::scale>::template forward<U, U1, T>(*this);
      // } else if constexpr (requires { scale_conversion_t<typename U1::scale, typename U::scale>::template backward<U, U1, T>(*this); }) {
      //   return scale_conversion_t<typename U1::scale, typename U::scale>::template backward<U, U1, T>(*this);
      } else if constexpr (requires { scale_conversion_t<typename U::scale, typename U1::scale>{}; }) {
        return scale_conversion_t<typename U::scale, typename U1::scale>::template forward<U, U1, T>(*this);
      } else if constexpr (requires { scale_conversion_t<typename U1::scale, typename U::scale>{}; }) {
        return scale_conversion_t<typename U1::scale, typename U::scale>::template backward<U, U1, T>(*this);
      } else if constexpr (requires { unit_conversion_t<U, U1, T>::factor; }) {
        return {this->value * unit_conversion_t<U, U1, T>::factor};
      } else if constexpr (requires { unit_conversion_t<U1, U, T>::factor; }) {
        return {this->value / unit_conversion_t<U1, U, T>::factor};
      } else {
        static_assert(false, "No conversion factor available between these units.");
        return {0};
      }
    }

    [[nodiscard]]
    inline std::string to_string() const noexcept {
      std::string str { };
      str.append(std::to_string(value));
      str.append(" [");
      str.append(U::symbol());
      str.append(":");
      str.append(typeid(T).name());
      str.append("]");
      return str;
    }
  };

  template <QuantityConcept Q, typename T1>
    requires(not QuantityConcept<T1>)
  Q operator/(const T1& lhs, const Q& rhs) {
    return {lhs / rhs->value};
  }

  template <QuantityConcept Q, typename T1>
    requires(not QuantityConcept<T1>)
  Q operator*(const T1& lhs, const Q& rhs) {
    return rhs * lhs;
  }

  template<typename U, typename T>
  using Q = quantity<U, T>;
}

export template<typename U, typename T>
std::ostream &operator<<(std::ostream &o, const quantify::quantity<U, T> &quantity) {
  o << quantity.to_string();
  return o;
}