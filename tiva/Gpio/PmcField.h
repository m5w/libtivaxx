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

#ifndef TIVA_GPIO_PMCFIELD_H
#define TIVA_GPIO_PMCFIELD_H

#include <cstdint>

#include "tiva/Field/EnumeratedField.h"
#include "tiva/Field/Field.h"
#include "tiva/Gpio/GpioPinIdentifier.h"

namespace tiva {

namespace detail {

template <GpioPinIdentifier PmcFieldGpioPinIdentifier> class PmcField;

template <>
class PmcField<GpioPinIdentifier::Pb0>
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit PmcField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

  using FieldValueType = FieldType::ValueType;

public:
  using ValueType = FieldValueType;

  static constexpr auto Usb0Id() { return PmcField(FieldType::make<0>()); }

  static constexpr auto Uart1Rx() { return PmcField(FieldType::make<1>()); }

  static constexpr auto Timer2Ccp0() { return PmcField(FieldType::make<7>()); }
};

template <>
class PmcField<GpioPinIdentifier::Pb1>
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit PmcField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

  using FieldValueType = FieldType::ValueType;

public:
  using ValueType = FieldValueType;

  static constexpr auto Usb0Vbus() { return PmcField(FieldType::make<0>()); }

  static constexpr auto Uart1Tx() { return PmcField(FieldType::make<1>()); }

  static constexpr auto Timer2Ccp1() { return PmcField(FieldType::make<7>()); }
};

template <>
class PmcField<GpioPinIdentifier::Pb2>
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit PmcField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

  using FieldValueType = FieldType::ValueType;

public:
  using ValueType = FieldValueType;

  static constexpr auto I2c0Scl() { return PmcField(FieldType::make<3>()); }

  static constexpr auto Timer3Ccp0() { return PmcField(FieldType::make<7>()); }
};

template <>
class PmcField<GpioPinIdentifier::Pb3>
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit PmcField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

  using FieldValueType = FieldType::ValueType;

public:
  using ValueType = FieldValueType;

  static constexpr auto I2c0Sda() { return PmcField(FieldType::make<3>()); }

  static constexpr auto Timer3Ccp1() { return PmcField(FieldType::make<7>()); }
};

template <>
class PmcField<GpioPinIdentifier::Pb4>
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit PmcField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

  using FieldValueType = FieldType::ValueType;

public:
  using ValueType = FieldValueType;

  static constexpr auto AnalogInput0() {
    return PmcField(FieldType::make<0>());
  }

  static constexpr auto Ssi2Clk() { return PmcField(FieldType::make<2>()); }

  static constexpr auto Modulator0Pwm2() {
    return PmcField(FieldType::make<4>());
  }

  static constexpr auto Timer1Ccp0() { return PmcField(FieldType::make<7>()); }

  static constexpr auto Can0Rx() { return PmcField(FieldType::make<8>()); }
};

template <>
class PmcField<GpioPinIdentifier::Pb5>
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit PmcField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

  using FieldValueType = FieldType::ValueType;

public:
  using ValueType = FieldValueType;

  static constexpr auto AnalogInput1() {
    return PmcField(FieldType::make<0>());
  }

  static constexpr auto Ssi2Fss() { return PmcField(FieldType::make<2>()); }

  static constexpr auto Modulator0Pwm3() {
    return PmcField(FieldType::make<4>());
  }

  static constexpr auto Timer1Ccp1() { return PmcField(FieldType::make<7>()); }

  static constexpr auto Can0Tx() { return PmcField(FieldType::make<8>()); }
};

template <>
class PmcField<GpioPinIdentifier::Pb6>
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit PmcField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

  using FieldValueType = FieldType::ValueType;

public:
  using ValueType = FieldValueType;

  static constexpr auto Ssi2Rx() { return PmcField(FieldType::make<2>()); }

  static constexpr auto Modulator0Pwm0() {
    return PmcField(FieldType::make<4>());
  }

  static constexpr auto Timer0Ccp0() { return PmcField(FieldType::make<7>()); }
};

template <>
class PmcField<GpioPinIdentifier::Pb7>
    : public EnumeratedField<Field<std::uint32_t, 4>> {
public:
  using FieldType = Field<std::uint32_t, 4>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit PmcField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

  using FieldValueType = FieldType::ValueType;

public:
  using ValueType = FieldValueType;

  static constexpr auto Ssi2Tx() { return PmcField(FieldType::make<2>()); }

  static constexpr auto Modulator0Pwm1() {
    return PmcField(FieldType::make<4>());
  }

  static constexpr auto Timer0Ccp1() { return PmcField(FieldType::make<7>()); }
};

} // namespace detail

} // namespace tiva

#endif // TIVA_GPIO_PMCFIELD_H
