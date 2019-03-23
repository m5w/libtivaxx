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

#ifndef TIVA_FIELD_BITNUMBER_H
#define TIVA_FIELD_BITNUMBER_H

#include <limits>

#include "tiva/Type/LclosedIntervalNumber.h"

namespace tiva {

template <class Value> class BitNumber {
public:
  using BitNumberValueType = decltype(std::numeric_limits<Value>::digits);

private:
  using BitNumberNumberType =
      LclosedIntervalNumber<BitNumberValueType, 0,
                            std::numeric_limits<Value>::digits>;
  BitNumberValueType V;

  constexpr explicit BitNumber(const BitNumberNumberType BN) : V(BN) {}

public:
  template <BitNumberValueType BitNumberValue>
  static constexpr BitNumber make() {
    return BitNumber(BitNumberNumberType::template make<BitNumberValue>());
  }

  constexpr operator BitNumberValueType() const { return this->V; }
};

} // namespace tiva

#endif // TIVA_FIELD_BITNUMBER_H
