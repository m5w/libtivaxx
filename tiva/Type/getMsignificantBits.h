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

#ifndef TIVA_TYPE_GETMSIGNIFICANTBITS_H
#define TIVA_TYPE_GETMSIGNIFICANTBITS_H

#include <limits>

#include "tiva/Type/LclosedIntervalNumber.h"
#include "tiva/Type/getLsignificantBits.h"

namespace tiva {

namespace detail {

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

} // namespace detail

} // namespace tiva

#endif // TIVA_TYPE_GETMSIGNIFICANTBITS_H
