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

#ifndef TIVA_REGISTER_REGISTERFIELD_H
#define TIVA_REGISTER_REGISTERFIELD_H

#include "tiva/Register/ReadRegisterField.h"
#include "tiva/Register/RegisterBitNumber.h"
#include "tiva/Register/UNSAFE_RegisterField.h"

namespace tiva {

template <class RegisterFieldFieldType,
          typename detail::RegisterBitNumber<
              typename RegisterFieldFieldType::ValueType>::ValueType
              RegisterFieldLsignificantRegisterBitNumberValue>
class RegisterField;

template <class RegisterFieldFieldType,
          typename detail::RegisterBitNumber<
              typename RegisterFieldFieldType::ValueType>::ValueType
              RegisterFieldLsignificantRegisterBitNumberValue>
class RegisterField : public detail::UNSAFE_RegisterField<
                          RegisterFieldFieldType,
                          RegisterFieldLsignificantRegisterBitNumberValue> {
public:
  using FieldType = RegisterFieldFieldType;
  static constexpr auto LsignificantRegisterBitNumberValue{
      RegisterFieldLsignificantRegisterBitNumberValue};
  using ReadRegisterFieldType =
      detail::ReadRegisterField<FieldType, LsignificantRegisterBitNumberValue>;

private:
  using UNSAFE_RegisterFieldType =
      detail::UNSAFE_RegisterField<FieldType,
                                   LsignificantRegisterBitNumberValue>;

public:
  constexpr explicit RegisterField(const FieldType RegisterFieldField)
      : UNSAFE_RegisterFieldType(RegisterFieldField) {}

  constexpr bool operator==(const RegisterField &RhandSide) const {
    return UNSAFE_RegisterFieldType::operator==(RhandSide);
  }
};

} // namespace tiva

#endif // TIVA_REGISTER_REGISTERFIELD_H
