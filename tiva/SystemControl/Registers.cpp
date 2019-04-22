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

#include "tiva/SystemControl/Registers.h"

namespace tiva {

namespace detail {

tiva::Register<
    tiva::RwMemorymappedRegister<std::uint32_t>, 0x0000'0000,
    GpioPortFRunModeClockGatingControl, GpioPortERunModeClockGatingControl,
    GpioPortDRunModeClockGatingControl, GpioPortCRunModeClockGatingControl,
    GpioPortBRunModeClockGatingControl, GpioPortARunModeClockGatingControl>
    Rcgcgpio(tiva::RwMemorymappedRegister<std::uint32_t>(0x400F'E000 + 0x608));

} // namespace detail

} // namespace tiva
