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

#ifndef TIVA_GPIO_GPIOPORT_H
#define TIVA_GPIO_GPIOPORT_H

#include <cstdint>

#include "tiva/Gpio/GpioPinAfselFieldType.h"
#include "tiva/Gpio/GpioPinDenFieldType.h"
#include "tiva/Gpio/GpioPinIdentifier.h"
#include "tiva/Gpio/GpioPinOdeFieldType.h"
#include "tiva/Gpio/GpioPinPmcFieldType.h"
#include "tiva/Register/Register.h"
#include "tiva/Register/RwMemorymappedRegister.h"
#include "tiva/SystemControl/BaseGpioPort.h"

namespace tiva {

template <GpioPortIdentifier GpioPortGpioPortIdentifier> class GpioPort;

template <>
class GpioPort<GpioPortIdentifier::B>
    : public detail::BaseGpioPort<GpioPortIdentifier::B> {
  static constexpr std::uint32_t BaseAddress{0x4005'9000};
  static Register<RwMemorymappedRegister<std::uint32_t>, 0x0000'0000,
                  detail::GpioPinAfselFieldType<GpioPinIdentifier::Pb7>,
                  detail::GpioPinAfselFieldType<GpioPinIdentifier::Pb6>,
                  detail::GpioPinAfselFieldType<GpioPinIdentifier::Pb5>,
                  detail::GpioPinAfselFieldType<GpioPinIdentifier::Pb4>,
                  detail::GpioPinAfselFieldType<GpioPinIdentifier::Pb3>,
                  detail::GpioPinAfselFieldType<GpioPinIdentifier::Pb2>,
                  detail::GpioPinAfselFieldType<GpioPinIdentifier::Pb1>,
                  detail::GpioPinAfselFieldType<GpioPinIdentifier::Pb0>>
      Gpioafsel;
  static Register<RwMemorymappedRegister<std::uint32_t>, 0x0000'0000,
                  detail::GpioPinOdeBitNumber<GpioPinIdentifier::Pb7>,
                  detail::GpioPinOdeBitNumber<GpioPinIdentifier::Pb6>,
                  detail::GpioPinOdeBitNumber<GpioPinIdentifier::Pb5>,
                  detail::GpioPinOdeBitNumber<GpioPinIdentifier::Pb4>,
                  detail::GpioPinOdeBitNumber<GpioPinIdentifier::Pb3>,
                  detail::GpioPinOdeBitNumber<GpioPinIdentifier::Pb2>,
                  detail::GpioPinOdeBitNumber<GpioPinIdentifier::Pb1>,
                  detail::GpioPinOdeBitNumber<GpioPinIdentifier::Pb0>>
      Gpioodr;
  static Register<RwMemorymappedRegister<std::uint32_t>, 0x0000'0000,
                  detail::GpioPinDenFieldType<GpioPinIdentifier::Pb7>,
                  detail::GpioPinDenFieldType<GpioPinIdentifier::Pb6>,
                  detail::GpioPinDenFieldType<GpioPinIdentifier::Pb5>,
                  detail::GpioPinDenFieldType<GpioPinIdentifier::Pb4>,
                  detail::GpioPinDenFieldType<GpioPinIdentifier::Pb3>,
                  detail::GpioPinDenFieldType<GpioPinIdentifier::Pb2>,
                  detail::GpioPinDenFieldType<GpioPinIdentifier::Pb1>,
                  detail::GpioPinDenFieldType<GpioPinIdentifier::Pb0>>
      Gpioden;
  static Register<RwMemorymappedRegister<std::uint32_t>, 0x0000'0000,
                  detail::GpioPinPmcFieldType<GpioPinIdentifier::Pb7>,
                  detail::GpioPinPmcFieldType<GpioPinIdentifier::Pb6>,
                  detail::GpioPinPmcFieldType<GpioPinIdentifier::Pb5>,
                  detail::GpioPinPmcFieldType<GpioPinIdentifier::Pb4>,
                  detail::GpioPinPmcFieldType<GpioPinIdentifier::Pb3>,
                  detail::GpioPinPmcFieldType<GpioPinIdentifier::Pb2>,
                  detail::GpioPinPmcFieldType<GpioPinIdentifier::Pb1>,
                  detail::GpioPinPmcFieldType<GpioPinIdentifier::Pb0>>
      Gpiopctl;
};

} // namespace tiva

#endif // TIVA_GPIO_GPIOPORT_H
