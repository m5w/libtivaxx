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

#ifndef TIVA_FIELD_BASEFIELD_H
#define TIVA_FIELD_BASEFIELD_H

namespace tiva {

namespace detail {

template <class FieldValueType> class BaseField;

template <class FieldValueType>
constexpr bool operator==(const BaseField<FieldValueType> &LhandSide,
                          const BaseField<FieldValueType> &RhandSide) {
  return LhandSide.V == RhandSide.V;
}

template <class FieldValueType> class BaseField {
  using ValueType = FieldValueType;
  ValueType V;

protected:
  BaseField() = default;

  constexpr explicit BaseField(const ValueType FieldValue) : V(FieldValue) {}

public:
  constexpr operator ValueType() const { return this->V; }

  friend constexpr bool operator==
      <>(const BaseField &LhandSide, const BaseField &RhandSide);
};

} // namespace detail

} // namespace tiva

#endif // TIVA_FIELD_BASEFIELD_H
