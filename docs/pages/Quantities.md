@page quantities Quantities

[TOC]

A **quantity** combines a numerical value with an associated unit. The unit provides meaning to the value, allowing it 
to be interpreted within a physical or conceptual domain.

# The quantity<Unit,DataType> class

In **Quantify** values are managed by the @ref quantify::quantity class template. This class implements unit related 
logic delegating the ownership of the value itself to the specified data type.

## Constructing a Quantity

The @ref quantify::quantity class template needs two arguments for its specialization:

- **Unit**: Specifies the associated unit for the quantity. Can be a [unit expression](unit_expressions.html).
- **Type**: The underlying data type used to store the numerical value. See [Underlying Data Type](#underlying-data-type) for details.

The constructor takes a value of specified underlying data type and stores a copy inside the quantity. Here is an example:

```c++
// Quantity representing 1 second with a float
quantify::quantity<quantify::time::seconds, float> some_time_quantity {1.0f};
```

### Type Aliasing

Using a type alias, one can write the same in a more readable way:

```c++
using namespace quantify;

template <typename Unit>
using measure = quantify::quantity<Unit, float>;

measure<time::seconds> some_time_quantity {1.0f};
```

This is specially useful because it decouples the unit from the underlying type. It avoids having to specify the type 
for each quantity, which may be error-prone in large code bases. It also makes it easy to change the type later if needed. 
Some use cases may even create more than one alias for different purposes. For instance, a physics engine dealing with 
both continuous and discrete algorithms may use two aliases as follows:

```c++
template <typename Unit>
using continuous = quantify::quantity<Unit, float>;

template <typename Unit>
using discrete = quantify::quantity<Unit, int>;
```

## Type Deduction

More often than not, quantities will be the result of operations involving other quantities. There are several ways to 
approach this depending on how much the algorithm needs to be _tied down_ to specific units and types.

The first option is to explicitly state the unit and type:

```c++
// dist: quantity<distance::mile, float>
//   dt: quantity<time::hours, float>
quantity<frac<distance::meter, time::seconds>, float> vel {dist / dt};
```

No surprises here, the result will be a quantity with units [_m/s_] and of type `float`. Since the input quantities are 
of different units, there will be a temporary quantity with units [_mi/h_] which will be [converted](getting_started.html#unit-and-scale-conversions) 
to [_m/s_] on construction of `vel`.

Alternatively, the [unit scale](scales.html) can be specified instead using the @ref quantify::Quantity concept. This has the 
result of accepting any quantity of any unit as long as it belongs to that scale. It avoids unnecessary unit conversions 
while still fully checking for consistency:

```c++
// dist: quantity<distance::mile, float>
//   dt: quantity<time::hours, float>
Quantity<frac<distance::scale, time::scale>> auto vel {dist / dt};

Quantity<frac<time::scale, mass::scale>> auto nonsense {dist / dt}; // Compilation Error
```

The associated unit for `vel` will be the same as that for the temporary value being passed to the constructor, which in 
this case is [_mi/h_]. On the other hand, the variable `nonsense` will not compile because it is expecting a ratio of 
time over mass and cannot be initialized with a quantity of speed.

This works the same way for function parameters, allowing for fully [unit agnostic functions](unit_agnostic_functions.html) 
like this one:

```c++
auto compute_speed(Quantity<distance::scale> auto dist, Quantity<time::scale> auto dt) {
  return dist / dt;
}

// Or, using built-in aliases
auto compute_speed(distance::quantity auto dist, time::quantity auto dt) {
  return dist / dt;
}
```

@sa [Unit Expressions](unit_expressions.html)
@sa [Writing Unit-Agnostic Functions](unit_agnostic_functions.html)

## Accessing a Quantity's value

The underlying value is a public field, so it can be accessed directly:

```c++
quantity<time::seconds, float> t {3600.0f};

std::println("value: {} seconds", t.value);
```

The method [`value_as_base_unit()`](@ref quantify::quantity::value_as_base_unit) returns a copy of the value as converted to the corresponding base unit. For instance, 
calling it on any quantity of distance will return the equivalent amount in _Meters_.

```c++
quantity<time::days, float> t {365.0f};

std::println("value: {} seconds", t.value_as_base_unit());
```

## Ownership Model

This class implements value semantics, that is, the lifetime of the value is tied to the lifetime of the quantity. A value 
cannot be moved out of a quantity. Moreover, most operators return a new instance of quantity instead of modifying the 
operated quantity in place, similar to how arithmetic types behave in C++. The notable exception to this rule are naturally 
in place operators such as `+=` or `=`.

## Underlying Data Type

**Quantify** does not make the choice as to how or where the numerical value of a quantity is stored. This is deferred 
to the underlying data type, which is specified as a template argument to the @ref quantify::quantity class template.

```c++
using namespace quantify;

// Scalar quantities
quantity<time::seconds, int>   integer_quantity;
quantity<time::seconds, float> float_quantity;

// Vector quantity using OpenGL Mathematics (GLM)
quantity<time::seconds, glm::vec3> vector_quantity;
```

The underlying data type must be **default constructible** as well as **copy and move constructible**. It must be **copy 
assignable** using the `=` operator. It should also handle most, if not all, arithmetic and comparison operators. 
Since all arithmetic and comparison methods in @ref quantify::quantity are method templates, there is no requirement for 
the underlying data type to implement every single operator. If one, such as `+`, `<` or `==`, is not defined in some 
type `T`, then the corresponding @ref quantify::quantity specialization `quantity<Unit,T>` will be missing that definition 
as well. No compilation error or warning will be reported unless said missing operator is attempted to be used.

```c++
// String quantity, compiles but it's not very useful
quantity<time::seconds, std::string> str_quantity;

auto result = str_quantity * 2; // ERROR: invalid operands to binary expression.
                                //        std::string does not implement `operator*(int)`
```

## Data Type Conversions

In general, operating on quantities with differing underlying data types will result in unpredictable type conversions. 
It is recommended that all the quantities used in an expression be of the same type. In order to cast a quantity to a 
different type, one must create a new quantity with the desired type.

```c++
quantity<time::seconds, int> integer_q;
quantity<time::seconds, float> float_q {integer_q};
```