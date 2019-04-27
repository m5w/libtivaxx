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

#ifndef TIVA_SYSTEMCONTROL_GPIOPORTRCGCFIELDLSIGNIFICANTREGISTERBITNUMBER_H
#define TIVA_SYSTEMCONTROL_GPIOPORTRCGCFIELDLSIGNIFICANTREGISTERBITNUMBER_H

#include <type_traits>

#include "tiva/SystemControl/GpioPortIdentifier.h"

namespace tiva {

namespace detail {

template <GpioPortIdentifier GpioPortRcgcBitNumberGpioPortIdentifier>
class GpioPortRcgcFieldLsignificantRegisterBitNumber;

template <>
class GpioPortRcgcFieldLsignificantRegisterBitNumber<GpioPortIdentifier::A>
    : public std::integral_constant<int, 0> {};

template <>
class GpioPortRcgcFieldLsignificantRegisterBitNumber<GpioPortIdentifier::B>
    : public std::integral_constant<int, 1> {};

template <>
class GpioPortRcgcFieldLsignificantRegisterBitNumber<GpioPortIdentifier::C>
    : public std::integral_constant<int, 2> {};

template <>
class GpioPortRcgcFieldLsignificantRegisterBitNumber<GpioPortIdentifier::D>
    : public std::integral_constant<int, 3> {};

template <>
class GpioPortRcgcFieldLsignificantRegisterBitNumber<GpioPortIdentifier::E>
    : public std::integral_constant<int, 4> {};

template <>
class GpioPortRcgcFieldLsignificantRegisterBitNumber<GpioPortIdentifier::F>
    : public std::integral_constant<int, 5> {};

} // namespace detail

} // namespace tiva

#endif // TIVA_SYSTEMCONTROL_GPIOPORTRCGCFIELDLSIGNIFICANTREGISTERBITNUMBER_H
