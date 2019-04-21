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

#include "tiva/Field/FieldIsValueValid.h"
#include "tiva/Field/UNSAFE_Field.h"

namespace tiva {

template <class FieldFieldType, class FieldIsValueValidType =
                                    detail::FieldIsValueValid<FieldFieldType>>
class DerivedField;

template <class FieldFieldType, class FieldIsValueValidType>
class DerivedField
    : public detail::UNSAFE_Field<typename FieldFieldType::ValueType,
                                  FieldFieldType::SizeValue> {
public:
  using FieldType = FieldFieldType;
  using IsValueValidType = FieldIsValueValidType;

private:
  using FieldValueType = typename FieldType::ValueType;

public:
  using ValueType = FieldValueType;

private:
  using UNSAFE_FieldType =
      detail::UNSAFE_Field<ValueType, FieldType::SizeValue>;

  constexpr explicit DerivedField(const FieldType FieldField)
      : UNSAFE_FieldType(FieldField) {}

public:
  static constexpr bool isValueValid(const ValueType FieldValue) {
    constexpr IsValueValidType IsValueValid;
    return FieldType::isValueValid(FieldValue) && IsValueValid(FieldValue);
  }

  template <ValueType FieldValue> static constexpr DerivedField make() {
    static_assert(isValueValid(FieldValue));
    return DerivedField(FieldType::template make<FieldValue>());
  }

  static DerivedField UNSAFE_make(const ValueType FieldValue) {
    return DerivedField(FieldType::UNSAFE_make(FieldValue));
  }
};

} // namespace tiva

#endif // TIVA_FIELD_DERIVEDFIELD_H
