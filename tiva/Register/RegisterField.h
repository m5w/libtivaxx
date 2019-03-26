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

#include <limits>

#include "tiva/Field/Field.h"
#include "tiva/Type/LclosedIntervalNumber.h"

namespace tiva {

template <class ValueType>
constexpr ValueType
getMsignificantBits(const LclosedIntervalNumber<
                    decltype(std::numeric_limits<ValueType>::digits), 0,
                    std::numeric_limits<ValueType>::digits + 1>
                        MsignificantBitsCount) {
  if (MsignificantBitsCount == 0)
    return 0;

  return getLsignificantBits<ValueType>(MsignificantBitsCount)
         << (std::numeric_limits<ValueType>::digits - MsignificantBitsCount);
}

namespace {

template <class RegisterValueType>
using RegisterBitNumber =
    LclosedIntervalNumber<decltype(
                              std::numeric_limits<RegisterValueType>::digits),
                          0, std::numeric_limits<RegisterValueType>::digits>;

} // namespace

template <class RegisterFieldFieldType,
          typename RegisterBitNumber<
              typename RegisterFieldFieldType::ValueType>::ValueType
              RegisterFieldLsignificantRegisterBitNumberValue>
class RegisterField {
public:
  using FieldValueType = typename RegisterFieldFieldType::ValueType;

private:
  using ValueType = FieldValueType;
  static constexpr auto LsignificantRegisterBitNumber{
      RegisterBitNumber<ValueType>::template make<
          RegisterFieldLsignificantRegisterBitNumberValue>()};
  static_assert(
      (RegisterFieldFieldType::getMask() &
       getMsignificantBits<ValueType>(LsignificantRegisterBitNumber)) == 0);
  static constexpr auto Mask{RegisterFieldFieldType::getMask()
                             << LsignificantRegisterBitNumber};
  ValueType V;

  constexpr explicit RegisterField(
      const RegisterFieldFieldType RegisterFieldField)
      : V(RegisterFieldField << LsignificantRegisterBitNumber) {}

public:
  static constexpr auto getMask() { return Mask; }

  template <FieldValueType RegisterFieldFieldValue>
  static constexpr RegisterField make() {
    return RegisterField(
        RegisterFieldFieldType::template make<RegisterFieldFieldValue>());
  }

  static RegisterField
  UNSAFE_make(const RegisterFieldFieldType RegisterFieldField) {
    return RegisterField(RegisterFieldField);
  }

  constexpr operator ValueType() const { return this->V; }
};

} // namespace tiva

#endif // TIVA_REGISTER_REGISTERFIELD_H
