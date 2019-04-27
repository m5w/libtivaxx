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

#ifndef TIVA_GPIO_GPIOPINODEFIELDTYPE_H
#define TIVA_GPIO_GPIOPINODEFIELDTYPE_H

#include "tiva/Gpio/GpioPinIdentifier.h"
#include "tiva/Gpio/GpioPinOdeFieldLsignificantRegisterBitNumber.h"
#include "tiva/Gpio/OdeField.h"
#include "tiva/Register/RegisterField.h"

namespace tiva {

namespace detail {

template <GpioPinIdentifier GpioPinOdeFieldGpioPinIdentifier>
using GpioPinOdeFieldType =
    RegisterField<OdeField, GpioPinOdeFieldLsignificantBitNumber<
                                GpioPinOdeFieldGpioPinIdentifier>::value>;

} // namespace detail

} // namespace tiva

#endif // TIVA_GPIO_GPIOPINODEFIELDTYPE_H
