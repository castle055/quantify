
<h1 align="center">
  <br>
  <img src="./logo/name_logo.png" alt="Quantify<>" width="200">
</h1>

<h4 align="center">An extensible C++ units library</h4>

<p align="center">
<img alt="Language" src="https://img.shields.io/badge/LANG-C%2B%2B-blue?&style=for-the-badge&logo=c%2B%2B&logoColor=blue">
<img alt="GitHub" src="https://img.shields.io/github/license/castle055/quantify?style=for-the-badge">
<img alt="GitHub tag (latest SemVer)" src="https://img.shields.io/github/v/tag/castle055/quantify?color=%23fcae1e&label=latest&sort=semver&style=for-the-badge">
</p>

<p align="center">
  <a href="#overview">Overview</a> •
  <a href="#how-to-build">How To Build</a> •
  <a href="#usage">Usage</a> •
  <a href="#documentation">Documentation</a> •
  <a href="#license">License</a>
</p>

## Overview

**Quantify<>** is a C++ module library that keeps track of engineering units while performing conversions as needed. It does this with no runtime memory overhead by encoding units as template parameters. It is capable of deducing units from arithmetic operations as long as all the operands have units attached to them.

**Quantify<>** can reduce most unit expressions to their simplest representation. For instance, multiplying meters per second [m/s] and seconds [s] results in meters [m], not [(m/s)*s]. This is done via **recursive pattern matching** implemented through template specialization, so it happens at compile-time. Reduction rules can be found in [`reduce_rules.cppm`](./include/quantify/reduce_rules.cppm).

**Quantify<>** also provides a few concepts that can help make mathematical algorithms unit agnostic. Unit conversions are performed as needed. Here is a simple example implementing Newton's Second Law:

```cpp
using namespace quantify;

auto second_law(
  Quantity<mass::scale> auto mass,
  Quantity<frac<distance::scale, mul<time::scale, time::scale>>> auto acceleration
) {
  return mass * acceleration;
}
```

This function is unit and type agnostic. It accepts any quantity of mass and any quantity of acceleration and multiplies them taking into account unit conversion factors. The resultant unit will be deduced from the provided units. Using the metric system this would be [kg]x[m/(s^2)] = [(kg*m)/(s^2)] = [N]. However any other units can be used. The return unit scale can also be specified in the same manner and can be used for checking for unit inconsistensies within the function.

Implementing functions in this manner avoids having to overload them for every combination of units or having to manually convert units.

> **NOTE:** As of now, **Quantify<>** is limited to dealing with integer exponents. **Quantify<>** cannot deduce units accross square roots, logarithms and other complex operations. These need to be handled manually.

## How to Build

After cloning this repository, or otherwise getting a copy of this directory, configure the library by running the following CMake command in this directory:

```sh
#          Built type (Debug/Release)    Build dir  Generator
#     /--------------------------------\/--------\/-------\
cmake -DCMAKE_BUILD_TYPE:STRING=Release -B./build -G Ninja
```

### Build Quantify

Once the project is configured, the library can be build with the following command:

```sh
#      Build dir    Built type      Build target
#     /--------\/---------------\/----------------\
cmake -B./build --config Release --target quantify
```

### Build Documentation

Doxygen documentation can be build with the following command:

```sh
#      Build dir    Built type        Build target
#     /--------\/---------------\/---------------------\
cmake -B./build --config Release --target quantify_docs
```

### Build Unit Tests

Tests can be built either all at once or separately with the following commands:

#### Build all tests

```sh
#      Build dir    Built type          Build target
#     /--------\/---------------\/---------------------------\
cmake -B./build --config Release --target TEST_SUITE_quantify
```

#### Build only specified test file

```sh
#      Build dir    Built type          Build target
#     /--------\/---------------\/------------------------\
cmake -B./build --config Release --target TEST_<test_name>
```

## Usage

### Adding to CMake Project

Integrating this library into a CMake project is as simple as adding the following to the `CmakeLists.txt` file:

```cmake
include(FetchContent)

FetchContent_Declare(quantify
        GIT_REPOSITORY https://github.com/castle055/quantify.git
        GIT_TAG main # or a tag (check repository for latest version)
        FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(quantify)
```

The `quantify` namespace can then be made available by importing the module `quantify`:

```cpp
import quantify;

using namespace quantify;
```

### Declaring Quantities

Quantities with units can be declared using the `Q<UnitExpression, Type>` template. `UnitExpression` the unit and `Type` the underlying type where the value is stored. The requirements for `Type` are that it must implement all arithmetic operations as well as construction from number literals.

Units are organized in **scales** which represent physical properties. Some scales are _distance_, _mass_, _time_, _etc_. Each scale is implemented as a namespace with some metadata. Units belonging to a specific scale are then found within its namespace. This library defines all base scales in the **International System of Units** as well as most scales derived from them. A `no_unit` unit is also defined to accomodate for quantities that do not have a unit, such as ratios. The `no_unit` unit is also useful when defining a unit expression as a fraction where the numerator is 1, such as frequency [1/s]. The `no_unit` unit is a part of the `no_scale` unit scale.

Some examples of quantities:

```cpp
// Base units
Q<distance::meters, double> some_distance = 10.0;
Q<time::seconds, double> some_duration = 1.0;
Q<temperature::kelvin, double> some_temperature = 273.15;
Q<substance::mol, double> some_substance_quantity = 4.0;

// Derived units
Q<energy::kilojoule, double> some_energy = 1.0;
Q<pressure::hectopascals, double> some_pressure = 1.0;

// no_unit unit
Q<no_unit, double> some_number = 1.0;
```

Units can also be specified as expression. For this purpose, the templates `frac<Numerator, Denominator>` and `mul<Products...>` are used to represent fractions and multiplications. Due to the nature of units, this is enough to represent almost all possible units. The main limitation being fractional exponents, which this library has no way of representing.

Some examples of unit expressions:

```cpp
Q<frac<distance::meters, time::seconds>, double>  -> [m/s] (velocity)
Q<mul<force::newtons, distance::meters>, double>  -> [Nm]  (torque)
Q<frac<no_unit, time_seconds>, double>            -> [1/s] (frequency)
```

Derived units act as aliases to their corresponding base unit expressions. For instance `force::newtons` is an alias to:

```cpp
frac<
  mul<mass::kilograms, distance::meters>,
  mul<time::seconds, time::seconds>
>
```

### Enforcing Units

Sometimes, it is necessary to force conversion of a quantity to a specific unit. This is usefull, for instance, for printing values in a consistent manner. This can be done by calling the function `.as<UnitExpression>()`:

```cpp
auto some_distance;

auto in_meters = some_distance.as<distance::meters>();
// `in_meters` will be converted to meters if needed.
// A compile-time error will be thrown if such conversion is impossible.
```

### Declaring Custom Scales and Units

Units must be declared within a scale. This can be any of the provided scales or a custom one. Some macros are needed which can be found in [unit_macros.h](./include/quantify/unit_macros.h).

Here is an example of how to add a unit to the distance scale:

```cpp
#include "quantify/unit_macros.h"

namespace distance {
  //    Identifier       Symbol  Conversion Factor
  //  /-----------------\ /---\ /--------------| 
  UNIT(astronomical_unit, "AU", 150000000000, 1)
}
```

and creating a new scale with units:

```cpp
#include "quantify/unit_macros.h"

SCALE(data) {
  UNIT(bit, "b", 1, 1)
  UNIT(byte, "B", 8, 1)
  UNIT(kilobyte, "kB", 1024*8, 1)
  UNIT(megabyte, "kB", 1024*1024*8, 1)
}
```

The **conversion factor** is expressed with two integer numbers, corresponding to the numerator and denominator that, multiplied by the value of its unit, would yield the same value expressed in the base unit of the scale. Irrational units are unsupported.

### Custom Conversions between Units

Declaring a custom conversion factor between any two units can be done by specializing the struct `unit_conversion_t<FromUnit, ToUnit, Type>` such that `[ToUnit] = [FromUnit] * unit_conversion_t<FromUnit, ToUnit, Type>::factor`:

```cpp
template <typename T>
struct quantify::unit_conversion_t<some_unit, other_unit, T> {
  static constexpr double factor = 1.23;
};
```

It is not necessary to specialize a factor for both directions of conversion. Reverse conversions will be performed by dividing by the same factor.

### Custom Conversions between Scales

Sometimes, different units within a scale cannot be converted between each other just with a fractional factor. For instance, in order to convert between `temperature::kelvin` and `temperature::celsius`, addition or subtraction are required ([K] = [C] + 273.15). For these cases, it is recommended to declare two different scales and then declare a custom conversion as follows:

```cpp
SCALE_CONVERSION(scales::kelvin::scale, scales::celsius::scale)
  SCALE_FORWARD_CONVERSION(it - 273.15) // Conversion from Kelvin to Celsius
  SCALE_BACKWARD_CONVERSION(it + 273.15) // Conversion from Celsius to Kelvin
```

## Documentation

Documentation can be found [here](https://castle055.github.io/quantify/).

## License

GPL 3.0 &nbsp;&middot;&nbsp; [LICENSE.md](LICENSE.md)

---

> GitHub [@castle055](https://github.com/castle055) &nbsp;&middot;&nbsp;

