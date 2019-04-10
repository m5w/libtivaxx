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

#ifndef TIVA_FIELD_DERIVEDFIELD_H
#define TIVA_FIELD_DERIVEDFIELD_H

#include "tiva/Field/UNSAFE_Field.h"

namespace tiva {

template <class FieldFieldType, class FieldIsValueValidType>
class DerivedField
    : public detail::UNSAFE_Field<typename FieldFieldType::ValueType,
                                  FieldFieldType::SizeValue> {
public:
  using FieldType = FieldFieldType;
  using IsValueValidType = FieldIsValueValidType;
  using ValueType = typename FieldType::ValueType;

private:
  using UNSAFE_FieldType =
      detail::UNSAFE_Field<ValueType, FieldType::SizeValue>;

  constexpr explicit DerivedField(const FieldType FieldField)
      : UNSAFE_FieldType(FieldField) {}

public:
  using UNSAFE_FieldType::getMask;

  static constexpr bool isValueValid(const ValueType FieldFieldValue) {
    constexpr IsValueValidType IsValueValid;
    return FieldType::isValueValid(FieldFieldValue) &&
           IsValueValid(FieldFieldValue);
  }

  template <ValueType FieldFieldValue> static constexpr DerivedField make() {
    static_assert(isValueValid(FieldFieldValue));
    return DerivedField(FieldType::template make<FieldFieldValue>());
  }

  static DerivedField UNSAFE_make(const ValueType FieldFieldValue) {
    return DerivedField(FieldType::UNSAFE_make(FieldFieldValue));
  }
};

} // namespace tiva

#endif // TIVA_FIELD_DERIVEDFIELD_H
