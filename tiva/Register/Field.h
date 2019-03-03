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

#ifndef TIVA_REGISTER_FIELD_H
#define TIVA_REGISTER_FIELD_H

#include <limits>

namespace tiva {

template <class Value, decltype(std::numeric_limits<Value>::digits) LsbNumber,
          decltype(std::numeric_limits<Value>::digits) MsbNumber>
class Field {
  static_assert(LsbNumber >= 0 &&
                LsbNumber < std::numeric_limits<Value>::digits);
  static_assert(MsbNumber >= LsbNumber &&
                MsbNumber < std::numeric_limits<Value>::digits);
  static constexpr auto Mask{
      (std::numeric_limits<Value>::max() >>
       (std::numeric_limits<Value>::digits - (MsbNumber - LsbNumber + 1)))
      << LsbNumber};
  Value V;

public:
  static constexpr auto getMask() { return Mask; }

  static constexpr bool isValid(const Value V) { return (V & Mask) == V; }

  constexpr Field(const Value V) : V(V) {}

  constexpr auto getValue() const { return this->V; }

  using ValueType = Value;
};

template <class FieldType, typename FieldType::ValueType Value>
constexpr auto makeField() {
  static_assert(FieldType::isValid(Value));
  return FieldType(Value);
}

} // namespace tiva

#endif // TIVA_REGISTER_FIELD_H
