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

#define CAIRO_HAS_PDF_SURFACE true

#include "common.h"
#include "type_name.h"
#include <cassert>

#include <chrono>

#include "quantify/unit_macros.h"

import quantify;
import packtl;


using namespace quantify;
using namespace quantify::distance;
using namespace quantify::angle;
using namespace quantify::time;
using namespace quantify::mass;
using namespace quantify::volume;
using namespace quantify::speed;
using namespace quantify::temperature;

//! I know this can be checked at compile-time, but for the purpose of
//! consistency, I want ALL tests to fail/succeed at run-time.
//! To be clear, the check is done at compile-time but reported at
//! run-time.
template<typename U1, typename U2>
inline void assert_reduces_to() {
  if constexpr (std::is_same_v<typename U1::reduce, U2>) {
    std::cout << "[PASS] [" << U1::symbol() << "] reduces to [" << U2::symbol() << "]" << std::endl;
  } else {
    std::cerr << "[FAIL] [" << U1::symbol() << "] reduces to [" << U1::reduce::symbol() << "] (expected [" <<
      U2::symbol() << "])" << std::endl;
    // __assert_fail(("[" + U1::symbol() + "] reduces to [" + U2::symbol() + "]").c_str(), __FILE_NAME__, __LINE__, __ASSERT_FUNCTION);
    std::abort();
  }
}

template<typename U1>
struct assert_unit {
  //! I know this can be checked at compile-time, but for the purpose of
  //! consistency, I want ALL tests to fail/succeed at run-time.
  //! To be clear, the check is done at compile-time but reported at
  //! run-time.
  template<typename U2>
  static void reduces_to() {
    if constexpr (std::is_same_v<reduce<U1>, U2>) {
      std::cout << "[PASS] [" << U1::symbol() << "] reduces to [" << U2::symbol() << "]" << std::endl;
    } else {
      std::cerr << clean_type_name<reduce<U1>>() << std::endl;
      std::cerr << clean_type_name<U2>() << std::endl;
      std::cerr << "[FAIL] [" << U1::symbol() << "] reduces to [" << reduce<U1>::symbol() << "] (expected [" <<
        U2::symbol() << "])" << std::endl;
      // __assert_fail(("[" + U1::symbol() + "] reduces to [" + U2::symbol() + "]").c_str(), __FILE_NAME__, __LINE__, __ASSERT_FUNCTION);
      std::abort();
    }
  }

private:
  template <typename T>
  static std::string clean_type_name() {
    std::string deleted = "quantify::";
    std::string str{refl::type_name<T>};
    auto pos = str.find(deleted);
    while (pos != std::string::npos) {
      str.replace(pos, deleted.size(), "");
      pos = str.find(deleted);
    }

    return str;
  }
};

void setup() {
}

TEST("Factors") {
  Q<distance::meter, double> d1 {10};
  Q<distance::kilometer, double> d2 {1};

  std::cout << "d1: " << (d1) << std::endl;
  std::cout << "d1: " << (d1.as<distance::kilometer>()) << std::endl;
  std::cout << "d2: " << (d2) << std::endl;
  std::cout << "d2: " << (d2.as<distance::meter>()) << std::endl;
  std::cout << " *: " << (d1 * d2) << std::endl;

  return 0;
}

TEST("Unit reduction") {
//@formatter:off
  assert_unit   <frac<meter, frac<meter, seconds>>>               ::reduces_to<seconds>();
  assert_unit   <frac<meter, frac<seconds, meter>>>               ::reduces_to<frac<mul<meter,meter>,seconds>>();
  assert_unit   <frac<frac<meter, seconds>, seconds>>              ::reduces_to<frac<meter, mul<seconds, seconds>>>();
  assert_unit   <frac<seconds, seconds>>                            ::reduces_to<no_unit>();
  assert_unit   <frac<seconds, no_unit>>                            ::reduces_to<seconds>();
  assert_unit   <frac<no_unit, seconds>>                            ::reduces_to<frac<no_unit, seconds>>();
  assert_unit   <frac<no_unit, no_unit>>                            ::reduces_to<no_unit>();
  assert_unit   <mul<no_unit, no_unit>>                             ::reduces_to<no_unit>();
  assert_unit   <mul<meter>>                                       ::reduces_to<meter>();
  assert_unit   <mul<meter, no_unit>>                              ::reduces_to<meter>();
  assert_unit   <mul<no_unit, meter>>                              ::reduces_to<meter>();
  assert_unit   <mul<meter, frac<grams, meter>>>                  ::reduces_to<grams>();
  assert_unit   <mul<frac<grams, meter>, meter>>                  ::reduces_to<grams>();
  assert_unit   <mul<meter, frac<grams, seconds>>>                 ::reduces_to<frac<mul<meter, grams>, seconds>>();
  assert_unit   <mul<frac<grams, seconds>, meter>>                 ::reduces_to<frac<mul<meter, grams>, seconds>>();
  assert_unit   <frac<mul<meter, meter>, mul<meter, meter>>>    ::reduces_to<no_unit>();
  assert_unit   <frac<mul<meter, meter>, meter>>                 ::reduces_to<meter>();
  assert_unit   <frac<meter, mul<meter, meter>>>                 ::reduces_to<frac<no_unit, meter>>();
  assert_unit   <mul<frac<meter, seconds>, frac<meter, seconds>>> ::reduces_to<frac<mul<meter, meter>, mul<seconds, seconds>>>();
  assert_unit   <frac<mul<meter, mul<meter, seconds>, seconds>, mul<seconds, seconds, meter, seconds>>>
                                                                    ::reduces_to<frac<meter, seconds>>();
  assert_unit   <mul<mul<meter,seconds>,kilograms>>                ::reduces_to<mul<meter,seconds, kilograms>>();

  assert_unit   <mul<frac<meter, mul<seconds, seconds>>, seconds>> ::reduces_to<frac<meter, seconds>>();
  assert_unit   <mul<frac<meter, mul<seconds, seconds, seconds>>, seconds>>
                                                                    ::reduces_to<frac<meter, mul<seconds, seconds>>>();
  assert_unit   <mul<frac<mul<meter, meter>, mul<seconds, seconds>>, mul<meter, meter>>>
                                                                    ::reduces_to<frac<mul<meter, meter, meter, meter>, mul<seconds, seconds>>>();

//@formatter:on

  // mechanics::newton::second_law
  //   ::isolate<mechanics::newton::second_law::acceleration>
  //   ::substitute<mechanics::newton::second_law::force>(1.0)
  //   ::substitute<mechanics::newton::second_law::mass>(1.0);
  //
  // using second_law = mechanics::newton::second_law;
  // second_law::isolate<second_law::acceleration>
  //           ::substitute<second_law::force>(1.0)
  //           ::substitute<second_law::mass>(1.0);

  return 0;
}

TEST("Unit conversion") {
  Q<frac<meter,seconds>, double> vel = 100.0;
  std::cout << "v: " << vel << std::endl;
  std::cout << "v: " << vel.as<frac<kilometer, hours>>() << std::endl;

  Q<mul<meter,seconds>, double> something = 100.0;
  std::cout << "s: " << something << std::endl;
  std::cout << "s: " << something.as<mul<kilometer, hours>>() << std::endl;
  return 0;
}

TEST("Quantity comparison") {
  Q<frac<meter,seconds>, int> vel = 100.0;
  Q<frac<meter,seconds>, int> vel1 = 150.0;
  Q<frac<meter,hours>, int> vel2 = 150.0;
  Q<mul<meter,seconds>, int> something = 100.0;

  if (vel < vel1) {}
  if (vel > vel1) {}
  if (vel <= vel1) {}
  if (vel >= vel1) {}
  if (vel == vel1) {}
  if (vel != vel1) {}
  if (vel < vel2) {}
  if (vel > vel2) {}
  if (vel <= vel2) {}
  if (vel >= vel2) {}
  if (vel == vel2) {}
  if (vel != vel2) {}
  // if (vel < something) {}
  // if (vel == something) {}

  // std::cout << "s: " << something << std::endl;
  // std::cout << "s: " << something.as<mul<kilometer, hours>>() << std::endl;
  return 0;
}

template <typename U>
using value = Q<reduce<U>, double>;

auto compute_speed(distance::quantity auto dist, time::quantity auto dt) {
  return dist / dt;
}

TEST("Example") {
  using joules = frac<mul<kilograms, meter, meter>, mul<seconds, seconds>>;
  using newtons = frac<mul<kilograms, meter>, mul<seconds, seconds>>;
  using namespace power;

  // Water
  value<kelvin> T_ci = 303;
  T_ci.as<celsius>().as<kelvin>();
  value<frac<kilograms, seconds>> m_c = 0.2;
  // Dimensions
  value<meter> L = 70;
  value<millimeter> D_i = 25;
  // Oil
  value<kelvin> T_hi = 373;
  value<kelvin> T_ho = 333;
  value<frac<kilograms, seconds>> m_h = 0.1;

  // Water properties @ 310K
  value<frac<joules, mul<kilograms,kelvin>>> cp_w = 4178;
  value<frac<mul<newtons,seconds>,mul<meter,meter>>> mu_w = 725e-6;
  value<no_unit> Pr_w = 4.85;
  value<frac<watts,mul<meter,kelvin>>> k_w = 0.625;

  // Water properties @ 310K
  value<frac<joules, mul<kilograms,kelvin>>> cp_oil = 2131;
  value<frac<mul<newtons,seconds>,mul<meter,meter>>> mu_oil = 3.25e-2;
  value<frac<watts,mul<meter,kelvin>>> k_oil = 0.138;

  auto q_oil = m_h * cp_oil * (T_hi - T_ho);

  auto T_co = T_ci + q_oil / (m_c * cp_w);

  std::cout << "Temperature: " << T_co << std::endl;
  std::cout << "Temperature: " << T_co.as<celsius>() << std::endl;
  std::cout << "Heat Flux: " << q_oil.as<watts>() << std::endl;
  std::cout << "Heat Flux: " << q_oil.as<kilowatts>() << std::endl;
  std::cout << "Heat Flux: " << q_oil.as<megawatts>() << std::endl;

  value<kilowatts> p1 {1.2345};
  value<seconds> s1{1.234};
  std::cout << "P: " << p1*s1 << std::endl;
  std::cout << "P: " << p1*s1*s1 << std::endl;
  std::cout << "P: " << (p1*s1*s1).as<frac<mul<grams, meter, meter>, seconds>>() << std::endl;
  std::cout << "P: " << p1.as<watts>() << std::endl;
  std::cout << "P: " << p1.as<kilowatts>() << std::endl;
  std::cout << "P: " << p1.as<megawatts>() << std::endl;
  std::cout << "P: " << p1.as<frac<mul<kilograms, meter, meter>, mul<seconds, seconds, seconds>>>() << std::endl;

  return 0;
}

