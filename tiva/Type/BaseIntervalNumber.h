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

#ifndef TIVA_TYPE_BASEINTERVALNUMBER_H
#define TIVA_TYPE_BASEINTERVALNUMBER_H

namespace tiva {

namespace detail {

template <class IntervalNumberValueType> class BaseIntervalNumber;

template <class IntervalNumberValueType>
constexpr bool
operator==(const BaseIntervalNumber<IntervalNumberValueType> &LhandSide,
           const BaseIntervalNumber<IntervalNumberValueType> &RhandSide) {
  return LhandSide.V == RhandSide.V;
}

template <class IntervalNumberValueType> class BaseIntervalNumber {
  using ValueType = IntervalNumberValueType;
  ValueType V;

protected:
  BaseIntervalNumber() = default;

  constexpr explicit BaseIntervalNumber(const ValueType IntervalNumberValue)
      : V(IntervalNumberValue) {}

public:
  constexpr operator ValueType() const { return this->V; }

  friend constexpr bool operator==<>(const BaseIntervalNumber &LhandSide,
                                     const BaseIntervalNumber &RhandSide);
};

} // namespace detail

} // namespace tiva

#endif // TIVA_TYPE_BASEINTERVALNUMBER_H
