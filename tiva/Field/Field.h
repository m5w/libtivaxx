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

#include "tiva/Field/UNSAFE_Field.h"

namespace tiva {

template <class FieldValueType,
          typename detail::FieldSize<FieldValueType>::ValueType FieldSizeValue>
class Field;

template <class FieldValueType,
          typename detail::FieldSize<FieldValueType>::ValueType FieldSizeValue>
class Field : public detail::UNSAFE_Field<FieldValueType, FieldSizeValue> {
public:
  using ValueType = FieldValueType;
  static constexpr auto SizeValue{FieldSizeValue};

private:
  using UNSAFE_FieldType = detail::UNSAFE_Field<ValueType, SizeValue>;

  constexpr explicit Field(const ValueType FieldValue)
      : UNSAFE_FieldType(FieldValue) {}

public:
  using UNSAFE_FieldType::getMask;

  static constexpr bool isValueValid(const ValueType FieldValue) {
    return (FieldValue & getMask()) == FieldValue;
  }

  template <ValueType FieldValue> static constexpr Field make() {
    static_assert(isValueValid(FieldValue));
    return Field(FieldValue);
  }

  static Field UNSAFE_make(const ValueType FieldValue) {
    return Field(FieldValue);
  }
};

} // namespace tiva

#endif // TIVA_FIELD_FIELD_H
