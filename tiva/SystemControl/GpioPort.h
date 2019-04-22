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

#ifndef TIVA_SYSTEMCONTROL_GPIOPORT_H
#define TIVA_SYSTEMCONTROL_GPIOPORT_H

#include "tiva/SystemControl/Registers.h"

namespace tiva {

namespace detail {

template <class GpioPortGpioPortRunModeClockGatingControlType> class GpioPort;

template <class GpioPortGpioPortRunModeClockGatingControlType> class GpioPort {
  using GpioPortRunModeClockGatingControlType =
      GpioPortGpioPortRunModeClockGatingControlType;

public:
  GpioPort() {
    Rcgcgpio
        .write(GpioPortRunModeClockGatingControlType::template make<
               RunModeClockGatingControlField::Enabled()>())
        .write();
  }

  ~GpioPort() {
    Rcgcgpio
        .write(GpioPortRunModeClockGatingControlType::template make<
               RunModeClockGatingControlField::Disabled()>())
        .write();
  }
};

} // namespace detail

using GpioPortF = detail::GpioPort<detail::GpioPortFRunModeClockGatingControl>;
using GpioPortE = detail::GpioPort<detail::GpioPortERunModeClockGatingControl>;
using GpioPortD = detail::GpioPort<detail::GpioPortDRunModeClockGatingControl>;
using GpioPortC = detail::GpioPort<detail::GpioPortCRunModeClockGatingControl>;
using GpioPortB = detail::GpioPort<detail::GpioPortBRunModeClockGatingControl>;
using GpioPortA = detail::GpioPort<detail::GpioPortARunModeClockGatingControl>;

} // namespace tiva

#endif // TIVA_SYSTEMCONTROL_GPIOPORT_H
