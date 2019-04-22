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

#include "tiva/SystemControl/GpioPort.h"

namespace tiva {

namespace detail {

template class detail::GpioPort<detail::GpioPortFRunModeClockGatingControl>;
template class detail::GpioPort<detail::GpioPortERunModeClockGatingControl>;
template class detail::GpioPort<detail::GpioPortDRunModeClockGatingControl>;
template class detail::GpioPort<detail::GpioPortCRunModeClockGatingControl>;
template class detail::GpioPort<detail::GpioPortBRunModeClockGatingControl>;
template class detail::GpioPort<detail::GpioPortARunModeClockGatingControl>;

} // namespace detail

} // namespace tiva
