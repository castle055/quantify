@page installation_guide Installation & Build Guide

[TOC]

# Installation

Quantify's source code is composed of C++ modules and a header file containing some preprocessor macros. The best way to integrate Quantify into a project is with CMake by using `FetchContent_Declare()`:

```cmake
include(FetchContent)

FetchContent_Declare(quantify
    GIT_REPOSITORY https://github.com/castle055/quantify.git
    GIT_TAG v2.0.0 # or any other tag, ie: 'main', 'dev', 'v1.0.0', ...
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(quantify)
```

This will make the library available as the target `quantify`, which can then be linked against:

```cmake
add_executable(MyExecutable)
target_link_libraries(MyExecutable PRIVATE quantify)
```

Only the main `quantify` target is exported. Documentation and tests are exported only if CMake is called from Quantify's root directory. This is true when [building from source](#building-from-source) but not with `FetchContent`.

Some of the features of this library, such as [custom units and unit scales](custom_scales_n_units.html), require the use of preprocessor macros. These can be found in [Preprocessor Macros](group__preprocessor__macros.html) and can be included in any source file with:

```c++
#include <quantify/unit_macros.hpp>
```

## Requirements

- CMake version >=4.0
- Clang version >=19

> [!note]
> Other compilers may gain support as implementation of C++ modules mature. Currently, compiling with Clang is necessary for features such as `import std;`.

## Non-CMake Projects

If using CMake is not an option, the alternative is to manually copy the `include/quantify/` directory into the projects path such that module dependency scanning can find Quantify modules.

Of course, this can be automated with tools such as [GIT submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules), which will also make it easier to update later. In all cases, the compiler must be called such that it can find the module files. This is unfortunately not fully standardized yet within the C++ ecosystem and the instructions on how to do this may differ from one build environment to another.

## Choosing A Version

While the `main` and `dev` tags can be used, the `main` tag being more stable. It is recommended to always pin a specific version such as `v2.0.0`.

```cmake
FetchContent_Declare(quantify
    ...            # Some examples:
    GIT_TAG dev    #  Latest commit, might be unstable
    GIT_TAG main   #  Latest stable commit
    GIT_TAG v2.0.0 #  Release version v2.0.0, stable, won't change with time
    ...
)
```

Check the [repository](https://github.com/castle055/quantify.git) for the latest release version.

The versioning scheme for Quantify follows the following pattern:

```
v<MAJOR>.<MINOR>.<PATCH>
```

This general idea is to follow the [Semantic Versioning Specification](https://semver.org).

---

# Building from source

The main reason for doing this is developing Quantify itself or its documentation. If intended for use as a dependency in another project, this is not necessary. For that see the [Installation](#installation) section above.

After cloning [the repository](https://github.com/castle055/quantify.git), or otherwise getting a copy of the root directory, configure the library by running the following CMake command in the root directory:

```sh
#          Built type (Debug/Release)    Build dir  Generator
#     /--------------------------------\/--------\/-------\
cmake -DCMAKE_BUILD_TYPE:STRING=Release -B./build -G Ninja
```

## Build Quantify

Once the project is configured, the library can be built with the following command:

```sh
#      Build dir    Built type      Build target
#     /--------\/---------------\/----------------\
cmake -B./build --config Release --target quantify
```

## Build Documentation

Doxygen documentation can be built with the following command:

```sh
#      Build dir    Built type        Build target
#     /--------\/---------------\/---------------------\
cmake -B./build --config Release --target quantify_docs
```

This website will be built and placed in `docs/build/html`. Latex documentation and man pages are also generated and placed in `docs/build`.

## Build Unit Tests

Test files can be found in the `test/` folder and can be built either all at once or separately:

```sh
# To build the entire test suite
cmake -B./build --config Release --target TEST_SUITE_quantify

# To build only a specific test file
cmake -B./build --config Release --target TEST_<test_name>
```

> [!note]
> The `test/common/` directory contains test infrastructure and not actual tests.
