# Copyright (c) 2024-2025, Víctor Castillo Agüero.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


################################################################################
#[[                            PROJECT OVERVIEW                              ]]#
################################################################################
#                                                                Quantify<>    #
#                                                                              #
#[[  AVAILABLE OPTIONS:                                                      ]]#
#      - QUANTIFY_BUILD_TESTS ............................. DEV_MODE only, ON  #
#            whether or not tests should be built                              #
#      - QUANTIFY_BUILD_DOCS .............................. DEV_MODE only, ON  #
#            whether or not the documentation should be built                  #
#                                                                              #
#[[  CMAKE STRUCTURE:                                                        ]]#
#      - Project setup                                                         #
#      - Configure dependencies                                                #
#      - Configure Quantify<>                                                  #
#      - Configure tests                                                       #
#      - Configure Doxygen documentation                                       #
#                                                                              #
################################################################################


################################################################################
#[[                              PROJECT SETUP                               ]]#
################################################################################
#[[                          PREVENT IN-TREE BUILD                           ]]#
if (CMAKE_SOURCE_DIR STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Create a `build/` directory and call `cmake ..` from there.")
endif ()

#[[                          CHECK DEVELOPER MODE                            ]]#
set(QUANTIFY_DEV_MODE OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(QUANTIFY_DEV_MODE ON)
endif ()

#[[                         DEVELOPER MODE OPTIONS                           ]]#
if(QUANTIFY_DEV_MODE)
    option(QUANTIFY_BUILD_TESTS "whether or not tests should be built" ON)
    option(QUANTIFY_BUILD_DOCS "whether or not the documentation should be built" ON)
endif ()

# Select 'Release' build type by default.
# Has to be done before the call to `project()`.
# Use `-DCMAKE_BUILD_TYPE=` to override this.
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")

cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -pthread -fexperimental-library")

project(quantify LANGUAGES CXX C)

SET(QUANTIFY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(QUANTIFY_TEST_DIR ${QUANTIFY_DIR}/test)
SET(QUANTIFY_INCLUDE_DIR ${QUANTIFY_DIR}/include)
SET(QUANTIFY_SOURCE_DIR ${QUANTIFY_DIR}/src)
SET(QUANTIFY_CMAKE_DIR ${QUANTIFY_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${QUANTIFY_CMAKE_DIR}/Modules)


################################################################################
#[[                          CONFIGURE DEPENDENCIES                          ]]#
################################################################################
include(FetchContent)

#[[                           CONFIGURE CYD FABRIC                           ]]#
FetchContent_Declare(packtl
        GIT_REPOSITORY https://github.com/castle055/packtl.git
        GIT_TAG main
        FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(packtl)

################################################################################
#[[                           CONFIGURE CYD QUANTIFY                           ]]#
################################################################################
add_library(quantify)

FILE(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
        ${QUANTIFY_INCLUDE_DIR}/*.h
        ${QUANTIFY_INCLUDE_DIR}/*.hpp
        ${QUANTIFY_INCLUDE_DIR}/*.cpp
        ${QUANTIFY_SOURCE_DIR}/*.h
        ${QUANTIFY_SOURCE_DIR}/*.hpp
        ${QUANTIFY_SOURCE_DIR}/*.cpp
)
FILE(GLOB_RECURSE SRC_MOD_LIST CONFIGURE_DEPENDS
        ${QUANTIFY_INCLUDE_DIR}/*.cppm
        ${QUANTIFY_SOURCE_DIR}/*.cppm
)

target_include_directories(quantify PUBLIC ${QUANTIFY_INCLUDE_DIR})
target_compile_features(quantify PUBLIC cxx_std_23)
target_compile_options(quantify PUBLIC -stdlib=libc++ -pthread)
target_sources(quantify
        PUBLIC ${SRC_LIST}
        PUBLIC
        FILE_SET cxx_modules
        #        FILE_SET "${APP_NAME}_modfiles"
        TYPE CXX_MODULES
        BASE_DIRS ${QUANTIFY_SOURCE_DIR} ${QUANTIFY_INCLUDE_DIR}
        FILES ${SRC_MOD_LIST}
)
target_link_libraries(quantify PUBLIC packtl)


################################################################################
#[[                             CONFIGURE TESTS                              ]]#
################################################################################
include(${QUANTIFY_CMAKE_DIR}/ctest.cmake)

if (QUANTIFY_DEV_MODE AND QUANTIFY_BUILD_TESTS)
    target_configure_test_directory(quantify ${QUANTIFY_TEST_DIR})
endif ()


################################################################################
#[[                     CONFIGURE DOXYGEN DOCUMENTATION                      ]]#
################################################################################
include(${QUANTIFY_CMAKE_DIR}/docs.cmake)

if (QUANTIFY_DEV_MODE AND QUANTIFY_BUILD_DOCS)
    target_configure_doxygen(quantify
            DOXYFILE ${QUANTIFY_DIR}/docs/Doxyfile
            BASE_DIR ${QUANTIFY_DIR}
    )
endif ()

