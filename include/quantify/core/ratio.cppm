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

export module quantify.core:ratio;

export
namespace quantify {
  /*! @brief Static representation of a numerical ratio in the form of a fraction.
   *
   * @tparam T Type used to represent the numerator and the denominator
   * @tparam Num Numerator quantity
   * @tparam Den Denominator quantity
   */
  template<typename T, auto Num, auto Den>
  struct ratio {
    static constexpr T numerator   = Num;
    static constexpr T denominator = Den;
  };
}
