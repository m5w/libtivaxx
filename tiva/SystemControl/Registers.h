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

#ifndef TIVA_SYSTEMCONTROL_REGISTERS_H
#define TIVA_SYSTEMCONTROL_REGISTERS_H

#include <cstdint>

#include "tiva/Register/Register.h"
#include "tiva/Register/RegisterField.h"
#include "tiva/Register/RwMemorymappedRegister.h"
#include "tiva/SystemControl/GpioPortIdentifier.h"
#include "tiva/SystemControl/GpioPortRcgcBitNumber.h"
#include "tiva/SystemControl/GpioPortRcgcFieldType.h"
#include "tiva/SystemControl/RcgcField.h"

namespace tiva {

namespace detail {

extern Register<RwMemorymappedRegister<std::uint32_t>, 0x0000'0000,
                GpioPortRcgcFieldType<GpioPortIdentifier::F>,
                GpioPortRcgcFieldType<GpioPortIdentifier::E>,
                GpioPortRcgcFieldType<GpioPortIdentifier::D>,
                GpioPortRcgcFieldType<GpioPortIdentifier::C>,
                GpioPortRcgcFieldType<GpioPortIdentifier::B>,
                GpioPortRcgcFieldType<GpioPortIdentifier::A>>
    Rcgcgpio;

} // namespace detail

} // namespace tiva

#endif // TIVA_SYSTEMCONTROL_REGISTERS_H
