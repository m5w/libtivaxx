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

#ifndef TIVA_GPIO_PORTMUXCONTROLFIELD_H
#define TIVA_GPIO_PORTMUXCONTROLFIELD_H

#include <cstdint>

#include "tiva/Field/EnumeratedField.h"
#include "tiva/Field/Field.h"

namespace tiva {

namespace detail {

class Pb0PortMuxControlField
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit Pb0PortMuxControlField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

public:
  static constexpr auto Usb0Id() {
    return Pb0PortMuxControlField(FieldType::make<0>());
  }

  static constexpr auto Uart1Rx() {
    return Pb0PortMuxControlField(FieldType::make<1>());
  }

  static constexpr auto Timer2Ccp0() {
    return Pb0PortMuxControlField(FieldType::make<7>());
  }
};

class Pb1PortMuxControlField
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit Pb1PortMuxControlField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

public:
  static constexpr auto Usb0Vbus() {
    return Pb1PortMuxControlField(FieldType::make<0>());
  }

  static constexpr auto Uart1Tx() {
    return Pb1PortMuxControlField(FieldType::make<1>());
  }

  static constexpr auto Timer2Ccp1() {
    return Pb1PortMuxControlField(FieldType::make<7>());
  }
};

class Pb2PortMuxControlField
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit Pb2PortMuxControlField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

public:
  static constexpr auto I2c0Scl() {
    return Pb2PortMuxControlField(FieldType::make<3>());
  }

  static constexpr auto Timer3Ccp0() {
    return Pb2PortMuxControlField(FieldType::make<7>());
  }
};

class Pb3PortMuxControlField
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit Pb3PortMuxControlField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

public:
  static constexpr auto I2c0Sda() {
    return Pb3PortMuxControlField(FieldType::make<3>());
  }

  static constexpr auto Timer3Ccp1() {
    return Pb3PortMuxControlField(FieldType::make<7>());
  }
};

class Pb4PortMuxControlField
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit Pb4PortMuxControlField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

public:
  static constexpr auto AnalogInput0() {
    return Pb4PortMuxControlField(FieldType::make<0>());
  }

  static constexpr auto Ssi2Clk() {
    return Pb4PortMuxControlField(FieldType::make<2>());
  }

  static constexpr auto Modulator0Pwm2() {
    return Pb4PortMuxControlField(FieldType::make<4>());
  }

  static constexpr auto Timer1Ccp0() {
    return Pb4PortMuxControlField(FieldType::make<7>());
  }

  static constexpr auto Can0Rx() {
    return Pb4PortMuxControlField(FieldType::make<8>());
  }
};

class Pb5PortMuxControlField
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit Pb5PortMuxControlField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

public:
  static constexpr auto AnalogInput1() {
    return Pb5PortMuxControlField(FieldType::make<0>());
  }

  static constexpr auto Ssi2Fss() {
    return Pb5PortMuxControlField(FieldType::make<2>());
  }

  static constexpr auto Modulator0Pwm3() {
    return Pb5PortMuxControlField(FieldType::make<4>());
  }

  static constexpr auto Timer1Ccp1() {
    return Pb5PortMuxControlField(FieldType::make<7>());
  }

  static constexpr auto Can0Tx() {
    return Pb5PortMuxControlField(FieldType::make<8>());
  }
};

class Pb6PortMuxControlField
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit Pb6PortMuxControlField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

public:
  static constexpr auto Ssi2Rx() {
    return Pb6PortMuxControlField(FieldType::make<2>());
  }

  static constexpr auto Modulator0Pwm0() {
    return Pb6PortMuxControlField(FieldType::make<4>());
  }

  static constexpr auto Timer0Ccp0() {
    return Pb6PortMuxControlField(FieldType::make<7>());
  }
};

class Pb7PortMuxControlField
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit Pb7PortMuxControlField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

public:
  static constexpr auto Ssi2Tx() {
    return Pb7PortMuxControlField(FieldType::make<2>());
  }

  static constexpr auto Modulator0Pwm1() {
    return Pb7PortMuxControlField(FieldType::make<4>());
  }

  static constexpr auto Timer0Ccp1() {
    return Pb7PortMuxControlField(FieldType::make<7>());
  }
};

} // namespace detail

} // namespace tiva

#endif // TIVA_GPIO_PORTMUXCONTROLFIELD_H
