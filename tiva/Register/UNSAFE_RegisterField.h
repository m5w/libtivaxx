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

#ifndef TIVA_REGISTER_UNSAFE_REGISTERFIELD_H
#define TIVA_REGISTER_UNSAFE_REGISTERFIELD_H

#include "tiva/Register/BaseRegisterField.h"
#include "tiva/Register/RegisterBitNumber.h"
#include "tiva/Type/getMsignificantBits.h"

namespace tiva {

namespace detail {

template <class RegisterFieldFieldType,
          typename RegisterBitNumber<
              typename RegisterFieldFieldType::ValueType>::ValueType
              RegisterFieldLsignificantRegisterBitNumberValue>
class UNSAFE_RegisterField;

template <class RegisterFieldFieldType,
          typename RegisterBitNumber<
              typename RegisterFieldFieldType::ValueType>::ValueType
              RegisterFieldLsignificantRegisterBitNumberValue>
class UNSAFE_RegisterField : public BaseRegisterField<RegisterFieldFieldType> {
  using FieldType = RegisterFieldFieldType;
  static constexpr auto LsignificantRegisterBitNumberValue{
      RegisterFieldLsignificantRegisterBitNumberValue};
  using FieldValueType = typename FieldType::ValueType;
  using ValueType = FieldValueType;
  static constexpr auto LsignificantRegisterBitNumber{RegisterBitNumber<
      ValueType>::template make<LsignificantRegisterBitNumberValue>()};
  static_assert(
      (FieldType::getMask() &
       getMsignificantBits<ValueType>(LsignificantRegisterBitNumber)) == 0);
  static constexpr auto Mask{FieldType::getMask()
                             << LsignificantRegisterBitNumber};

protected:
  UNSAFE_RegisterField() = default;

private:
  using BaseRegisterFieldType = BaseRegisterField<FieldType>;

protected:
  constexpr explicit UNSAFE_RegisterField(const ValueType RegisterFieldValue)
      : BaseRegisterFieldType(RegisterFieldValue) {}

  constexpr explicit UNSAFE_RegisterField(const FieldType RegisterFieldField)
      : BaseRegisterFieldType(RegisterFieldField
                              << LsignificantRegisterBitNumber) {}

public:
  static constexpr auto getMask() { return Mask; }
};

} // namespace detail

} // namespace tiva

#endif // TIVA_REGISTER_UNSAFE_REGISTERFIELD_H
