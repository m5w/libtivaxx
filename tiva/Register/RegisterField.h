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

#include "tiva/Field/BitNumber.h"
#include "tiva/Field/Field.h"

namespace tiva {

template <class Value>
constexpr Value getNumbermsignificantBits(
    const decltype(std::numeric_limits<Value>::digits) Number) {
  if (Number == 0)
    return 0;

  return getNumberlsignificantBits<Value>(Number)
         << (std::numeric_limits<Value>::digits - Number);
}

template <class FieldType,
          typename BitNumber<typename FieldType::FieldValueType>::
              BitNumberValueType LsbNumberValue>
class RegisterField {
  using FieldTypeValue = typename FieldType::FieldValueType;
  static constexpr auto LsbNumber{
      BitNumber<FieldTypeValue>::template make<LsbNumberValue>()};
  static_assert((FieldType::getMask() &
                 getNumbermsignificantBits<FieldTypeValue>(LsbNumber)) == 0);
  static constexpr auto Mask{FieldType::getMask() << LsbNumber};
  FieldTypeValue Value;

  constexpr explicit RegisterField(const FieldType F)
      : Value(F << LsbNumber) {}

public:
  static constexpr auto getMask() { return Mask; }

  template <FieldTypeValue FieldValue> static constexpr RegisterField make() {
    return RegisterField(FieldType::template make<FieldValue>());
  }

  static RegisterField UNSAFE_make(const FieldType F) {
    return RegisterField(F);
  }

  constexpr operator FieldTypeValue() const { return this->Value; }

  using FieldValueType = FieldTypeValue;
};

} // namespace tiva

#endif // TIVA_REGISTER_REGISTERFIELD_H
