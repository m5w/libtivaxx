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
#include "tiva/Type/LclosedIntervalNumber.h"

namespace tiva {

template <class ValueType>
constexpr ValueType
getLsignificantBits(const LclosedIntervalNumber<
                    decltype(std::numeric_limits<ValueType>::digits), 0,
                    std::numeric_limits<ValueType>::digits + 1>
                        LsignificantBitsCount) {
  if (LsignificantBitsCount == 0)
    return 0;

  return std::numeric_limits<ValueType>::max() >>
         (std::numeric_limits<ValueType>::digits - LsignificantBitsCount);
}

namespace {

template <class FieldValueType>
using FieldSize =
    LclosedIntervalNumber<decltype(
                              std::numeric_limits<FieldValueType>::digits),
                          1, std::numeric_limits<FieldValueType>::digits + 1>;

} // namespace

template <class FieldValueType,
          typename FieldSize<FieldValueType>::ValueType FieldSizeValue>
class Field : public BaseField<FieldValueType> {
public:
  using ValueType = FieldValueType;

private:
  static constexpr auto Size{
      FieldSize<ValueType>::template make<FieldSizeValue>()};
  static constexpr auto Mask{getLsignificantBits<ValueType>(Size)};
  using BaseFieldType = BaseField<ValueType>;

  constexpr explicit Field(const ValueType FieldValue)
      : BaseFieldType(FieldValue) {}

public:
  static constexpr auto getMask() { return Mask; }

  static constexpr bool isValueValid(const ValueType FieldValue) {
    return (FieldValue & Mask) == FieldValue;
  }

  template <ValueType FieldValue> static constexpr Field make() {
    static_assert(isValueValid(FieldValue));
    return Field(FieldValue);
  }

  static Field UNSAFE_make(const ValueType FieldValue) {
    return Field(FieldValue);
  }
};

template <class FieldFieldFieldType, class FieldFieldIsValueValid>
class FieldField : public BaseField<typename FieldFieldFieldType::ValueType> {
public:
  using ValueType = typename FieldFieldFieldType::ValueType;

private:
  using BaseFieldType = BaseField<ValueType>;

  constexpr explicit FieldField(const FieldFieldFieldType FieldFieldField)
      : BaseFieldType(FieldFieldField) {}

public:
  static constexpr auto getMask() { return FieldFieldFieldType::getMask(); }

  static constexpr bool isValueValid(const ValueType FieldFieldFieldValue) {
    constexpr FieldFieldIsValueValid IsValueValid;
    return FieldFieldFieldType::isValueValid(FieldFieldFieldValue) &&
           IsValueValid(FieldFieldFieldValue);
  }

  template <ValueType FieldFieldFieldValue>
  static constexpr FieldField make() {
    static_assert(isValueValid(FieldFieldFieldValue));
    return FieldField(
        FieldFieldFieldType::template make<FieldFieldFieldValue>());
  }

  static FieldField UNSAFE_make(const FieldFieldFieldType FieldFieldField) {
    return FieldField(FieldFieldField);
  }
};

} // namespace tiva

#endif // TIVA_FIELD_FIELD_H
