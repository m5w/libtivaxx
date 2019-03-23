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

#ifndef TIVA_FIELD_FIELD_H
#define TIVA_FIELD_FIELD_H

#include <limits>

#include "tiva/Field/BaseField.h"
#include "tiva/Field/BitNumber.h"
#include "tiva/Field/FieldWidth.h"

namespace tiva {

template <class Value>
constexpr Value getNumberlsignificantBits(
    const decltype(std::numeric_limits<Value>::digits) Number) {
  if (Number == 0)
    return 0;

  return std::numeric_limits<Value>::max() >>
         (std::numeric_limits<Value>::digits - Number);
}

template <class Value,
          typename FieldWidth<Value>::FieldWidthValueType FieldWidthValue>
class Field : public BaseField<Value> {
  static constexpr auto FW{
      FieldWidth<Value>::template make<FieldWidthValue>()};
  static constexpr auto Mask{getNumberlsignificantBits<Value>(FW)};
  using BaseFieldType = BaseField<Value>;

  constexpr explicit Field(const Value FieldValue)
      : BaseFieldType(FieldValue) {}

public:
  static constexpr auto getMask() { return Mask; }

  static constexpr bool isValueValid(const Value FieldValue) {
    return (FieldValue & Mask) == FieldValue;
  }

  template <Value FieldValue> static constexpr Field make() {
    static_assert(isValueValid(FieldValue));
    return Field(FieldValue);
  }

  static Field UNSAFE_make(const Value FieldValue) {
    return Field(FieldValue);
  }

  using FieldValueType = Value;
};

} // namespace tiva

#endif // TIVA_FIELD_FIELD_H
