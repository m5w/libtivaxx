// Copyright (C) 2019 Matthew Marting
//
// This file is part of libtiva++.
//
// libtiva++ is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libtiva++ is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with libtiva++.  If not, see <https://www.gnu.org/licenses/>.

#ifndef TIVA_REGISTER_BITWIDTH_H
#define TIVA_REGISTER_BITWIDTH_H

#include <limits>

namespace tiva {

template <class Value,
          decltype(std::numeric_limits<Value>::digits) MinimumBitwidthValue>
class Bitwidth {
  using BitwidthType = Bitwidth<Value, MinimumBitwidthValue>;
  static_assert(MinimumBitwidthValue >= 0);
  using BitwidthValueType = decltype(std::numeric_limits<Value>::digits);
  BitwidthValueType V;
  constexpr Bitwidth(const BitwidthValueType V) : V(V) {}

public:
  template <BitwidthValueType V> static constexpr Bitwidth makeBitwidth() {
    static_assert((V >= MinimumBitwidthValue) &&
                  (V < std::numeric_limits<Value>::digits));
    return Bitwidth(V);
  }

  constexpr BitwidthValueType getValue() const { return V; }
};

template <class Value,
          decltype(std::numeric_limits<Value>::digits) MinimumBitwidthValue,
          decltype(std::numeric_limits<Value>::digits) V>
constexpr Bitwidth<Value, MinimumBitwidthValue> makeBitwidth() {
  return Bitwidth<Value, MinimumBitwidthValue>::template makeBitwidth<V>();
}

} // namespace tiva

#endif // TIVA_REGISTER_BITWIDTH_H
