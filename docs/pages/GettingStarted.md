@page getting_started Getting Started

[TOC]

# Introduction

**Quantify** is C++ library that deals with engineering units. It can deduce units across mathematical expressions and 
reduce those units to their simplest representation. That is, if a speed [_m/s_] is multiplied by time [_s_], the 
resulting unit will be a distance [_m_], and not [_s*m/s_]. Units are checked for consistency at compile time and unit 
conversions are performed when needed.

**Quantify** allows for code to become fully **unit-agnostic**. Functions can specify which [unit scales](scales.html) 
their parameters belong to (ie: mass, distance, time,...) thus allowing for any unit in those scales to be used. Here is 
a short example of an implementation of Newton's second law as a unit-agnostic function:

```cpp
auto second_law(
  mass::quantity auto m,
  Quantity<frac<distance::scale, mul<time::scale, time::scale>>> auto a
) {
  return m * a; // Force = Mass * Acceleration
}
```

Nowhere on this function is any unit specified, but the output will always be convertible to _Newtons_. The inputs `m` 
and `a` can be of any unit as long as they represent mass and acceleration respectively. This is a powerful feature 
that enables writing unit-consistent code without actually caring about which units will eventually be used.

For more information, see [Writing Unit-Agnostic Functions](unit_agnostic_functions.html)

# Key Concepts

The library is developed around three main concepts: **Quantities**, **Units**, and **Unit Scales**.

**Units** represent your typical engineering units such as _Meters_ or _Seconds_, they can be combined using 
[unit expressions](unit_expressions.html) to represent more complex units such as _Newtons_ [_kg*m/s^2_].

[**Unit Scales**](scales.html) group units that can be converted using a rational conversion factor. For example, the 
_distance_ scale contains all the units that represent length quantities such as _Meters_ or _Miles_. In some cases, 
such as for temperature scales, units can be converted between different unit scales. See [Custom Conversions](custom_conversions.html) 
for a detailed explanation as to how or why this may be needed.

Lastly, [**Quantities**](quantities.html) are objects of the wrapper class @ref quantify::quantity which annotates a value with a 
unit. The unit is only relevant at compile time so there is no runtime memory overhead. This is the class that 
implements unit deduction logic.

@sa [Quantities](quantities.html)
@sa [Unit Expressions](unit_expressions.html)
@sa [Unit Scales](scales.html)

# Built-in and Custom Units

**Quantify** defines all base and derived units in the [International System of Units](https://en.wikipedia.org/wiki/International_System_of_Units). 
On top of that, Quantify also defines other non SI units such as those found in the [Imperial System](https://en.wikipedia.org/wiki/Imperial_units). 
More units may be added over time as the library evolves. Finally, Quantify allows for new units to be defined in existing 
scales. For instance, a new distance unit could be added like this:

```c++
UNIT_IN_SCALE(quantify::distance::scale, lunar_distance, "LD", 384400000, 1);
```

Where the unit _Lunar Distance_ [_LD_] is specified with a conversion factor of _384,400,000/1_ which corresponds 
to _1 Lunar Distance_ being _384,400,000 meters_ given that _meters_ are the base unit for the _distance_ scale. 
Similarly, more scales can also be added. See [Custom Scales and Units](custom_scales_n_units.html) for more information.

@sa [Base Units](group__base__units.html)
@sa [Derived Units](group__derived__units.html)
@sa [Custom Scales and Units](custom_scales_n_units.html)

# Unit and Scale Conversions

Units belonging to the same scale can always be converted among each other since they are related by a rational factor. 
For example, _Kilometers_ are in the same scale as _Miles_ (the _distance_ scale) and thus a quantity represented in 
either unit can always be converted to the other by multiplying or dividing by a factor. In this case, the factor would 
be computed at compile time from the individual defining factors for each unit:

$$([km]\rightarrow[m]): 1000[m]/1[km]$$
$$([mi]\rightarrow[m]): 1609[m]/1[mi]$$

Then,

$$([km]\rightarrow[mi]): ([km]\rightarrow[m])*([m]\rightarrow[mi])$$
$$([km]\rightarrow[mi]): \frac{([km]\rightarrow[m])}{([mi]\rightarrow[m])} = \frac{1000[m]/1[km]}{1609[m]/1[mi]} = \frac{1000[mi]}{1609[km]} \approx 0.6215 [mi/km]$$

So _Kilometers_ can be converted to _Miles_ by multiplying times _0.6215_. Similarly, _Miles_ can be converted to 
_Kilometers_ by dividing by the same factor. In **Quantify** terms, this is only possible because both units belong to 
the same scale and thus their defining factors are in terms of the same base unit, _Meters_, so they can be combined.

By default, units from different scales cannot be converted between one another.
That is, their values are not related by a conversion factor.
For instance, _1 meter_ cannot be converted to an equivalent amount of _seconds_.

There are cases, however, where it may make sense to establish a custom 
conversion between two different scales. Quantify can handle these cases by 
allowing custom scale conversions to be defined with the @ref SCALE_CONVERSION macro.

```c++
SCALE_CONVERSION(FromScale, ToScale)
    SCALE_FORWARD_CONVERSION(...)
    SCALE_BACKWARD_CONVERSION(...)
```

One specific example is that of the temperature scales. The units (_Celsius_, _Kelvin_ and _Fahrenheit_) all represent a quantity of temperature, but converting a value from one to another is not a simple question of multiplying by factor. An offset needs to be added or subtracted in each conversion.

```c++
SCALE_CONVERSION(scales::kelvin::scale, scales::celsius::scale)
    SCALE_FORWARD_CONVERSION(it - 273.15)
    SCALE_BACKWARD_CONVERSION(it + 273.15)

SCALE_CONVERSION(scales::celsius::scale, scales::fahrenheit::scale)
    SCALE_FORWARD_CONVERSION((it * 9 / 5) + 32)
    SCALE_BACKWARD_CONVERSION((it - 32) * 5 / 9)

SCALE_CONVERSION(scales::kelvin::scale, scales::fahrenheit::scale)
    SCALE_FORWARD_CONVERSION(((it - 273.15) * 9 / 5) + 32)
    SCALE_BACKWARD_CONVERSION(((it - 32) * 5 / 9) + 273.15)
```

Scale conversions are rarely performed automatically as they are inherently 
non-linear, the main way to invoke them is by [forcing unit conversions](forcing_units.html). 
Mathematical expressions usually cannot be made agnostic to non-linear conversions. 
For instance, formulas involving _Celsius_ don't work the same way if _Kelvin_ is 
used instead. On the other hand, Newton's second law of motion (_F=m*a_) works the 
same with _Kilograms_, _Pounds_, or _Metric Tons_. The unit for the output value 
will change, but the mathematical equality will hold.

@sa [Forcing Units and Performing Conversions](forcing_units.html)

# Installation

For the simplest case, using CMake, add this to the project's `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(quantify
    GIT_REPOSITORY https://github.com/castle055/quantify.git
    GIT_TAG <git-tag> # any version tag, ie: 'main', 'dev', 'v1.0.0', ... or a commit hash
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(quantify)
```

Then link the project's target against `quantify`:

```cmake
target_link_libraries(MyExecutable PRIVATE quantify)
```

@sa [Installation & Build Guide](installation_guide.html)
