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
#include "tiva/SystemControl/RunModeClockGatingControlField.h"

namespace tiva {

namespace detail {

using GpioPortFRunModeClockGatingControl =
    RegisterField<RunModeClockGatingControlField::FieldType, 5>;
using GpioPortERunModeClockGatingControl =
    RegisterField<RunModeClockGatingControlField::FieldType, 4>;
using GpioPortDRunModeClockGatingControl =
    RegisterField<RunModeClockGatingControlField::FieldType, 3>;
using GpioPortCRunModeClockGatingControl =
    RegisterField<RunModeClockGatingControlField::FieldType, 2>;
using GpioPortBRunModeClockGatingControl =
    RegisterField<RunModeClockGatingControlField::FieldType, 1>;
using GpioPortARunModeClockGatingControl =
    RegisterField<RunModeClockGatingControlField::FieldType, 0>;

extern Register<
    RwMemorymappedRegister<std::uint32_t>, 0x0000'0000,
    GpioPortFRunModeClockGatingControl, GpioPortERunModeClockGatingControl,
    GpioPortDRunModeClockGatingControl, GpioPortCRunModeClockGatingControl,
    GpioPortBRunModeClockGatingControl, GpioPortARunModeClockGatingControl>
    Rcgcgpio;

} // namespace detail

} // namespace tiva

#endif // TIVA_SYSTEMCONTROL_REGISTERS_H
