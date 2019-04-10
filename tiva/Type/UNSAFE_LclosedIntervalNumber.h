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

#ifndef TIVA_TYPE_UNSAFE_LCLOSEDINTERVALNUMBER_H
#define TIVA_TYPE_UNSAFE_LCLOSEDINTERVALNUMBER_H

#include "tiva/Type/BaseIntervalNumber.h"

namespace tiva {

namespace detail {

template <class IntervalNumberNumberType,
          IntervalNumberNumberType IntervalNumberIntervalLEndpoint,
          IntervalNumberNumberType IntervalNumberIntervalREndpoint>
class UNSAFE_LclosedIntervalNumber
    : public BaseIntervalNumber<IntervalNumberNumberType> {
  using NumberType = IntervalNumberNumberType;
  static constexpr auto IntervalLEndpoint{IntervalNumberIntervalLEndpoint};
  static constexpr auto IntervalREndpoint{IntervalNumberIntervalREndpoint};
  static_assert(IntervalLEndpoint < IntervalREndpoint);
  using ValueType = NumberType;
  using BaseIntervalNumberType = BaseIntervalNumber<ValueType>;

protected:
  static constexpr bool isValueValid(const ValueType IntervalNumberValue) {
    return (IntervalNumberValue >= IntervalLEndpoint) &&
           (IntervalNumberValue < IntervalREndpoint);
  }

  constexpr explicit UNSAFE_LclosedIntervalNumber(
      const ValueType IntervalNumberValue)
      : BaseIntervalNumberType(IntervalNumberValue) {}
};

} // namespace detail

} // namespace tiva

#endif // TIVA_TYPE_UNSAFE_LCLOSEDINTERVALNUMBER_H
