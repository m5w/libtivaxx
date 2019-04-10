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

#ifndef TIVA_TYPE_LCLOSEDINTERVALNUMBER_H
#define TIVA_TYPE_LCLOSEDINTERVALNUMBER_H

#include "tiva/Type/UNSAFE_LclosedIntervalNumber.h"

namespace tiva {

namespace detail {

template <class IntervalNumberNumberType,
          IntervalNumberNumberType IntervalNumberIntervalLEndpoint,
          IntervalNumberNumberType IntervalNumberIntervalREndpoint>
class LclosedIntervalNumber
    : public UNSAFE_LclosedIntervalNumber<IntervalNumberNumberType,
                                          IntervalNumberIntervalLEndpoint,
                                          IntervalNumberIntervalREndpoint> {
public:
  using NumberType = IntervalNumberNumberType;
  static constexpr auto IntervalLEndpoint{IntervalNumberIntervalLEndpoint};
  static constexpr auto IntervalREndpoint{IntervalNumberIntervalREndpoint};
  using ValueType = NumberType;

private:
  friend LclosedIntervalNumber<ValueType, IntervalLEndpoint + 1,
                               IntervalREndpoint>;
  friend LclosedIntervalNumber<ValueType, IntervalLEndpoint,
                               IntervalREndpoint - 1>;
  using UNSAFE_LclosedIntervalNumberType =
      UNSAFE_LclosedIntervalNumber<ValueType, IntervalLEndpoint,
                                   IntervalREndpoint>;

private:
  using UNSAFE_LclosedIntervalNumberType::isValueValid;

  constexpr explicit LclosedIntervalNumber(const ValueType IntervalNumberValue)
      : UNSAFE_LclosedIntervalNumberType(IntervalNumberValue) {}

public:
  template <ValueType IntervalNumberValue>
  static constexpr LclosedIntervalNumber make() {
    static_assert(isValueValid(IntervalNumberValue));
    return LclosedIntervalNumber(IntervalNumberValue);
  }

private:
  using IntervalLEndpointm1Type =
      LclosedIntervalNumber<ValueType, IntervalLEndpoint - 1,
                            IntervalREndpoint>;

public:
  constexpr operator IntervalLEndpointm1Type() const {
    return IntervalLEndpointm1Type(static_cast<ValueType>(*this));
  }

private:
  using IntervalREndpointp1Type =
      LclosedIntervalNumber<ValueType, IntervalLEndpoint,
                            IntervalREndpoint + 1>;

public:
  constexpr operator IntervalREndpointp1Type() const {
    return IntervalREndpointp1Type(static_cast<ValueType>(*this));
  }
};

} // namespace detail

} // namespace tiva

#endif // TIVA_TYPE_LCLOSEDINTERVALNUMBER_H
