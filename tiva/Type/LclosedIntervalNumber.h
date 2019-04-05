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

namespace tiva {

template <class IntervalNumberType, IntervalNumberType IntervalLEndpoint,
          IntervalNumberType IntervalREndpoint>
class LclosedIntervalNumber {
  static_assert(IntervalLEndpoint < IntervalREndpoint);
  friend LclosedIntervalNumber<IntervalNumberType, IntervalLEndpoint + 1,
                               IntervalREndpoint>;
  friend LclosedIntervalNumber<IntervalNumberType, IntervalLEndpoint,
                               IntervalREndpoint - 1>;

public:
  using ValueType = IntervalNumberType;

private:
  ValueType V;

  constexpr explicit LclosedIntervalNumber(const ValueType NumberValue)
      : V(NumberValue) {}

  static constexpr bool isValueValid(const ValueType NumberValue) {
    return (NumberValue >= IntervalLEndpoint) &&
           (NumberValue < IntervalREndpoint);
  }

public:
  template <ValueType NumberValue>
  static constexpr LclosedIntervalNumber make() {
    static_assert(isValueValid(NumberValue));
    return LclosedIntervalNumber(NumberValue);
  }

  constexpr operator ValueType() const { return this->V; }

private:
  using IntervalLEndpointm1Type =
      LclosedIntervalNumber<IntervalNumberType, IntervalLEndpoint - 1,
                            IntervalREndpoint>;

public:
  constexpr operator IntervalLEndpointm1Type() const {
    return IntervalLEndpointm1Type(this->V);
  }

private:
  using IntervalREndpointp1Type =
      LclosedIntervalNumber<IntervalNumberType, IntervalLEndpoint,
                            IntervalREndpoint + 1>;

public:
  constexpr operator IntervalREndpointp1Type() const {
    return IntervalREndpointp1Type(this->V);
  }
};

} // namespace tiva

#endif // TIVA_TYPE_LCLOSEDINTERVALNUMBER_H
