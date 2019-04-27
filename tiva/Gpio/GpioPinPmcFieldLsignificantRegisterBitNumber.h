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

#ifndef TIVA_GPIO_GPIOPINPMCFIELDLSIGNIFICANTREGISTERBITNUMBER_H
#define TIVA_GPIO_GPIOPINPMCFIELDLSIGNIFICANTREGISTERBITNUMBER_H

#include <type_traits>

#include "tiva/Gpio/GpioPinIdentifier.h"

namespace tiva {

namespace detail {

template <GpioPinIdentifier GpioPinPmcBitNumberGpioPinIdentifier>
class GpioPinPmcFieldLsignificantBitNumber;

template <>
class GpioPinPmcFieldLsignificantBitNumber<GpioPinIdentifier::Pb0>
    : public std::integral_constant<int, 0> {};

template <>
class GpioPinPmcFieldLsignificantBitNumber<GpioPinIdentifier::Pb1>
    : public std::integral_constant<int, 4> {};

template <>
class GpioPinPmcFieldLsignificantBitNumber<GpioPinIdentifier::Pb2>
    : public std::integral_constant<int, 8> {};

template <>
class GpioPinPmcFieldLsignificantBitNumber<GpioPinIdentifier::Pb3>
    : public std::integral_constant<int, 12> {};

template <>
class GpioPinPmcFieldLsignificantBitNumber<GpioPinIdentifier::Pb4>
    : public std::integral_constant<int, 16> {};

template <>
class GpioPinPmcFieldLsignificantBitNumber<GpioPinIdentifier::Pb5>
    : public std::integral_constant<int, 20> {};

template <>
class GpioPinPmcFieldLsignificantBitNumber<GpioPinIdentifier::Pb6>
    : public std::integral_constant<int, 24> {};

template <>
class GpioPinPmcFieldLsignificantBitNumber<GpioPinIdentifier::Pb7>
    : public std::integral_constant<int, 28> {};

} // namespace detail

} // namespace tiva

#endif // TIVA_GPIO_GPIOPINPMCFIELDLSIGNIFICANTREGISTERBITNUMBER_H
