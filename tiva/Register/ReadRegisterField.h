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

#ifndef TIVA_REGISTER_READREGISTERFIELD_H
#define TIVA_REGISTER_READREGISTERFIELD_H

#include "tiva/Register/RegisterBitNumber.h"
#include "tiva/Register/UNSAFE_RegisterField.h"

namespace tiva {

namespace detail {

template <class RegisterFieldFieldType,
          typename detail::RegisterBitNumber<
              typename RegisterFieldFieldType::ValueType>::ValueType
              RegisterFieldLsignificantRegisterBitNumberValue>
class ReadRegisterField;

template <class RegisterFieldFieldType,
          typename detail::RegisterBitNumber<
              typename RegisterFieldFieldType::ValueType>::ValueType
              RegisterFieldLsignificantRegisterBitNumberValue>
class ReadRegisterField
    : public UNSAFE_RegisterField<
          RegisterFieldFieldType,
          RegisterFieldLsignificantRegisterBitNumberValue> {
  using FieldType = RegisterFieldFieldType;
  static constexpr auto LsignificantRegisterBitNumberValue{
      RegisterFieldLsignificantRegisterBitNumberValue};
  using UNSAFE_RegisterFieldType =
      UNSAFE_RegisterField<FieldType, LsignificantRegisterBitNumberValue>;

public:
  using UNSAFE_RegisterFieldType::getMask;

private:
  using FieldValueType = typename FieldType::ValueType;
  using ValueType = FieldValueType;

public:
  static ReadRegisterField read(const ValueType RegisterValue) {
    return ReadRegisterField(RegisterValue & getMask());
  }

  ReadRegisterField() = default;

  constexpr explicit ReadRegisterField(const ValueType RegisterFieldValue)
      : UNSAFE_RegisterFieldType(RegisterFieldValue) {}

  constexpr bool operator==(const ReadRegisterField &RhandSide) const {
    return UNSAFE_RegisterFieldType::operator==(RhandSide);
  }
};

} // namespace detail

} // namespace tiva

#endif // TIVA_REGISTER_READREGISTERFIELD_H
