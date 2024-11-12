// Copyright (c) 2024, Víctor Castillo Agüero.
// SPDX-License-Identifier: GPL-3.0-or-later

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
  Q<distance::meters, double> d1 {10};
  Q<distance::kilometers, double> d2 {1};

  std::cout << "d1: " << (d1) << std::endl;
  std::cout << "d1: " << (d1.as<distance::kilometers>()) << std::endl;
  std::cout << "d2: " << (d2) << std::endl;
  std::cout << "d2: " << (d2.as<distance::meters>()) << std::endl;
  std::cout << " *: " << (d1 * d2) << std::endl;

  return 0;
}

TEST("Unit reduction") {
//@formatter:off
  assert_unit   <frac<meters, frac<meters, seconds>>>               ::reduces_to<seconds>();
  assert_unit   <frac<meters, frac<seconds, meters>>>               ::reduces_to<frac<mul<meters,meters>,seconds>>();
  assert_unit   <frac<frac<meters, seconds>, seconds>>              ::reduces_to<frac<meters, mul<seconds, seconds>>>();
  assert_unit   <frac<seconds, seconds>>                            ::reduces_to<no_unit>();
  assert_unit   <frac<seconds, no_unit>>                            ::reduces_to<seconds>();
  assert_unit   <frac<no_unit, seconds>>                            ::reduces_to<frac<no_unit, seconds>>();
  assert_unit   <frac<no_unit, no_unit>>                            ::reduces_to<no_unit>();
  assert_unit   <mul<no_unit, no_unit>>                             ::reduces_to<no_unit>();
  assert_unit   <mul<meters>>                                       ::reduces_to<meters>();
  assert_unit   <mul<meters, no_unit>>                              ::reduces_to<meters>();
  assert_unit   <mul<no_unit, meters>>                              ::reduces_to<meters>();
  assert_unit   <mul<meters, frac<grams, meters>>>                  ::reduces_to<grams>();
  assert_unit   <mul<frac<grams, meters>, meters>>                  ::reduces_to<grams>();
  assert_unit   <mul<meters, frac<grams, seconds>>>                 ::reduces_to<frac<mul<meters, grams>, seconds>>();
  assert_unit   <mul<frac<grams, seconds>, meters>>                 ::reduces_to<frac<mul<meters, grams>, seconds>>();
  assert_unit   <frac<mul<meters, meters>, mul<meters, meters>>>    ::reduces_to<no_unit>();
  assert_unit   <frac<mul<meters, meters>, meters>>                 ::reduces_to<meters>();
  assert_unit   <frac<meters, mul<meters, meters>>>                 ::reduces_to<frac<no_unit, meters>>();
  assert_unit   <mul<frac<meters, seconds>, frac<meters, seconds>>> ::reduces_to<frac<mul<meters, meters>, mul<seconds, seconds>>>();
  assert_unit   <frac<mul<meters, mul<meters, seconds>, seconds>, mul<seconds, seconds, meters, seconds>>>
                                                                    ::reduces_to<frac<meters, seconds>>();
  assert_unit   <mul<mul<meters,seconds>,kilograms>>                ::reduces_to<mul<meters,seconds, kilograms>>();

  assert_unit   <mul<frac<meters, mul<seconds, seconds>>, seconds>> ::reduces_to<frac<meters, seconds>>();
  assert_unit   <mul<frac<meters, mul<seconds, seconds, seconds>>, seconds>>
                                                                    ::reduces_to<frac<meters, mul<seconds, seconds>>>();
  assert_unit   <mul<frac<mul<meters, meters>, mul<seconds, seconds>>, mul<meters, meters>>>
                                                                    ::reduces_to<frac<mul<meters, meters, meters, meters>, mul<seconds, seconds>>>();

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
  quantity_t<frac<meters,seconds>, double> vel = 100.0;
  std::cout << "v: " << vel << std::endl;
  std::cout << "v: " << vel.as<frac<kilometers, hours>>() << std::endl;

  quantity_t<mul<meters,seconds>, double> something = 100.0;
  std::cout << "s: " << something << std::endl;
  std::cout << "s: " << something.as<mul<kilometers, hours>>() << std::endl;
  return 0;
}

TEST("Quantity comparison") {
  quantity_t<frac<meters,seconds>, int> vel = 100.0;
  quantity_t<frac<meters,seconds>, int> vel1 = 150.0;
  quantity_t<frac<meters,hours>, int> vel2 = 150.0;
  quantity_t<mul<meters,seconds>, int> something = 100.0;

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
  // std::cout << "s: " << something.as<mul<kilometers, hours>>() << std::endl;
  return 0;
}

template <typename U>
using value = quantity_t<reduce<U>, double>;

TEST("Example") {
  using joules = frac<mul<kilograms, meters, meters>, mul<seconds, seconds>>;
  using newtons = frac<mul<kilograms, meters>, mul<seconds, seconds>>;
  using namespace power;

  // Water
  value<kelvin> T_ci = 303;
  T_ci.as<celsius>().as<kelvin>();
  value<frac<kilograms, seconds>> m_c = 0.2;
  // Dimensions
  value<meters> L = 70;
  value<millimeter> D_i = 25;
  // Oil
  value<kelvin> T_hi = 373;
  value<kelvin> T_ho = 333;
  value<frac<kilograms, seconds>> m_h = 0.1;

  // Water properties @ 310K
  value<frac<joules, mul<kilograms,kelvin>>> cp_w = 4178;
  value<frac<mul<newtons,seconds>,mul<meters,meters>>> mu_w = 725e-6;
  value<no_unit> Pr_w = 4.85;
  value<frac<watts,mul<meters,kelvin>>> k_w = 0.625;

  // Water properties @ 310K
  value<frac<joules, mul<kilograms,kelvin>>> cp_oil = 2131;
  value<frac<mul<newtons,seconds>,mul<meters,meters>>> mu_oil = 3.25e-2;
  value<frac<watts,mul<meters,kelvin>>> k_oil = 0.138;

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
  std::cout << "P: " << (p1*s1*s1).as<frac<mul<grams, meters, meters>, seconds>>() << std::endl;
  std::cout << "P: " << p1.as<watts>() << std::endl;
  std::cout << "P: " << p1.as<kilowatts>() << std::endl;
  std::cout << "P: " << p1.as<megawatts>() << std::endl;
  std::cout << "P: " << p1.as<frac<mul<kilograms, meters, meters>, mul<seconds, seconds, seconds>>>() << std::endl;

  return 0;
}

