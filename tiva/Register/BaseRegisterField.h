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

#ifndef TIVA_REGISTER_BASEREGISTERFIELD_H
#define TIVA_REGISTER_BASEREGISTERFIELD_H

namespace tiva {

namespace detail {

template <class RegisterFieldFieldType> class BaseRegisterField;

template <class RegisterFieldFieldType>
constexpr bool
operator==(const BaseRegisterField<RegisterFieldFieldType> &LhandSide,
           const BaseRegisterField<RegisterFieldFieldType> &RhandSide) {
  return LhandSide.V == RhandSide.V;
}

template <class RegisterFieldFieldType> class BaseRegisterField {
  using FieldType = RegisterFieldFieldType;
  using FieldValueType = typename FieldType::ValueType;
  using ValueType = FieldValueType;
  ValueType V;

protected:
  BaseRegisterField() = default;

  constexpr explicit BaseRegisterField(const ValueType RegisterFieldValue)
      : V(RegisterFieldValue) {}

public:
  constexpr operator ValueType() const { return this->V; }

  friend constexpr bool operator==<>(const BaseRegisterField &LhandSide,
                                     const BaseRegisterField &RhandSide);
};

} // namespace detail

} // namespace tiva

#endif // TIVA_REGISTER_BASEREGISTERFIELD_H
