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

template <class Number, Number IntervalLEndpoint, Number IntervalREndpoint>
class LclosedIntervalNumber {
  Number Value;

  constexpr explicit LclosedIntervalNumber(
      const Number LclosedIntervalNumberValue)
      : Value(LclosedIntervalNumberValue) {}

  static constexpr bool isValueValid(const Number LclosedIntervalNumberValue) {
    return (LclosedIntervalNumberValue >= IntervalLEndpoint) &&
           (LclosedIntervalNumberValue < IntervalREndpoint);
  }

public:
  template <Number LclosedIntervalNumberValue>
  static constexpr LclosedIntervalNumber make() {
    static_assert(isValueValid(LclosedIntervalNumberValue));
    return LclosedIntervalNumber(LclosedIntervalNumberValue);
  }

  constexpr operator Number() const { return this->Value; }
};

} // namespace tiva

#endif // TIVA_TYPE_LCLOSEDINTERVALNUMBER_H
