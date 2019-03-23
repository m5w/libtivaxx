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

#ifndef TIVA_FIELD_FIELDWIDTH_H
#define TIVA_FIELD_FIELDWIDTH_H

#include <limits>

#include "tiva/Type/LclosedIntervalNumber.h"

namespace tiva {

template <class Value> class FieldWidth {
public:
  using FieldWidthValueType = decltype(std::numeric_limits<Value>::digits);

private:
  using FieldWidthNumberType =
      LclosedIntervalNumber<FieldWidthValueType, 1,
                            std::numeric_limits<Value>::digits + 1>;
  FieldWidthValueType V;

  constexpr explicit FieldWidth(const FieldWidthNumberType FW) : V(FW) {}

public:
  template <FieldWidthValueType FieldWidthValue>
  static constexpr FieldWidth make() {
    return FieldWidth(FieldWidthNumberType::template make<FieldWidthValue>());
  }

  constexpr operator FieldWidthValueType() const { return this->V; }
};

} // namespace tiva

#endif // TIVA_FIELD_FIELDWIDTH_H
