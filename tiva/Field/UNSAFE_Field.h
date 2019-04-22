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

#ifndef TIVA_FIELD_UNSAFE_FIELD_H
#define TIVA_FIELD_UNSAFE_FIELD_H

#include "tiva/Field/BaseField.h"
#include "tiva/Field/FieldSize.h"
#include "tiva/Type/getLsignificantBits.h"

namespace tiva {

namespace detail {

template <class FieldValueType,
          typename FieldSize<FieldValueType>::ValueType FieldSizeValue>
class UNSAFE_Field;

template <class FieldValueType,
          typename FieldSize<FieldValueType>::ValueType FieldSizeValue>
class UNSAFE_Field : public BaseField<FieldValueType> {
  using ValueType = FieldValueType;
  static constexpr auto SizeValue{FieldSizeValue};
  static constexpr auto Size{FieldSize<ValueType>::template make<SizeValue>()};
  static constexpr auto Mask{getLsignificantBits<ValueType>(Size)};

protected:
  UNSAFE_Field() = default;

private:
  using BaseFieldType = BaseField<ValueType>;

protected:
  constexpr explicit UNSAFE_Field(const ValueType FieldValue)
      : BaseFieldType(FieldValue) {}

public:
  static constexpr auto getMask() { return Mask; }
};

} // namespace detail

} // namespace tiva

#endif // TIVA_FIELD_UNSAFE_FIELD_H
