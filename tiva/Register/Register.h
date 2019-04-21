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

#ifndef TIVA_REGISTER_REGISTER_H
#define TIVA_REGISTER_REGISTER_H

#include <type_traits>
#include <utility>

#include "tiva/Register/RegisterBitNumber.h"
#include "tiva/Register/UNSAFE_RegisterField.h"

namespace tiva {

namespace detail {

template <class RRegisterFieldsRegisterType,
          class RRegisterFieldsReadRRegisterFieldsType,
          class RRegisterFieldsFieldType,
          class... RRegisterFieldsFieldsgep1Types>
class RRegisterFields;
template <class RRegisterFieldsRegisterType,
          class RRegisterFieldsReadWRegisterFieldsType,
          class... RRegisterFieldsFieldsTypes>
class RRegisterFieldsge0;
template <class ReadRRegisterFieldsRegisterType,
          class ReadRRegisterFieldsReadRRegisterFieldsType,
          class ReadRRegisterFieldsFieldType,
          class... ReadRRegisterFieldsFieldsgep1Types>
class ReadRRegisterFields;
template <class ReadRRegisterFieldsRegisterType,
          class ReadRRegisterFieldsReadWRegisterFieldsType,
          class... ReadRRegisterFieldsFieldsTypes>
class ReadRRegisterFieldsge0;

template <class RRegisterFieldsRegisterType,
          class RRegisterFieldsReadRRegisterFieldsType,
          class RRegisterFieldsFieldType>
inline bool
operator==(const RRegisterFields<RRegisterFieldsRegisterType,
                                 RRegisterFieldsReadRRegisterFieldsType,
                                 RRegisterFieldsFieldType> &LhandSide,
           const RRegisterFields<RRegisterFieldsRegisterType,
                                 RRegisterFieldsReadRRegisterFieldsType,
                                 RRegisterFieldsFieldType> &RhandSide) {
  return LhandSide.R == RhandSide.R;
}

template <class RRegisterFieldsRegisterType,
          class RRegisterFieldsReadRRegisterFieldsType,
          class RRegisterFieldsFieldType>
class RRegisterFields<RRegisterFieldsRegisterType,
                      RRegisterFieldsReadRRegisterFieldsType,
                      RRegisterFieldsFieldType> {
  using RegisterType = RRegisterFieldsRegisterType;
  using ReadRRegisterFieldsType = RRegisterFieldsReadRRegisterFieldsType;
  using FieldType = RRegisterFieldsFieldType;

protected:
  const RegisterType &R;

  explicit RRegisterFields(const RegisterType &RRegisterFieldsRegister)
      : R(RRegisterFieldsRegister) {}

public:
  friend bool operator==
      <>(const RRegisterFields &LhandSide, const RRegisterFields &RhandSide);

private:
  using FieldReadRegisterFieldType = typename FieldType::ReadRegisterFieldType;

public:
  auto read(FieldReadRegisterFieldType &F) const {
    const auto RegisterValue{this->R.read()};
    F = FieldReadRegisterFieldType::read(RegisterValue);
    return ReadRRegisterFieldsType(this->R, RegisterValue);
  }
};

template <class RRegisterFieldsRegisterType,
          class RRegisterFieldsReadRRegisterFieldsType,
          class RRegisterFieldsFieldType,
          class... RRegisterFieldsFieldsgep1Types>
class RRegisterFields
    : public RRegisterFields<RRegisterFieldsRegisterType,
                             RRegisterFieldsReadRRegisterFieldsType,
                             RRegisterFieldsFieldsgep1Types...> {
  using RegisterType = RRegisterFieldsRegisterType;
  using ReadRRegisterFieldsType = RRegisterFieldsReadRRegisterFieldsType;
  using FieldType = RRegisterFieldsFieldType;
  using RRegisterFieldsgep1Type =
      RRegisterFields<RegisterType, ReadRRegisterFieldsType,
                      RRegisterFieldsFieldsgep1Types...>;

protected:
  explicit RRegisterFields(const RegisterType &RRegisterFieldsRegister)
      : RRegisterFieldsgep1Type(RRegisterFieldsRegister) {}

public:
  using RRegisterFieldsgep1Type::read;

private:
  using FieldReadRegisterFieldType = typename FieldType::ReadRegisterFieldType;

public:
  auto read(FieldReadRegisterFieldType &F) const {
    const auto RegisterValue{this->R.read()};
    F = FieldReadRegisterFieldType::read(RegisterValue);
    return ReadRRegisterFieldsType(this->R, RegisterValue);
  }
};

template <class RRegisterFieldsRegisterType,
          class RRegisterFieldsReadWRegisterFieldsType,
          class... RRegisterFieldsFieldsTypes>
class RRegisterFieldsge0
    : public RRegisterFields<
          RRegisterFieldsRegisterType,
          ReadRRegisterFieldsge0<RRegisterFieldsRegisterType,
                                 RRegisterFieldsReadWRegisterFieldsType,
                                 RRegisterFieldsFieldsTypes...>,
          RRegisterFieldsFieldsTypes...> {
  using RegisterType = RRegisterFieldsRegisterType;
  using ReadWRegisterFieldsType = RRegisterFieldsReadWRegisterFieldsType;
  using RRegisterFieldsType = RRegisterFields<
      RegisterType,
      ReadRRegisterFieldsge0<RegisterType, ReadWRegisterFieldsType,
                             RRegisterFieldsFieldsTypes...>,
      RRegisterFieldsFieldsTypes...>;

public:
  using RRegisterFieldsType::read;

  explicit RRegisterFieldsge0(const RegisterType &RRegisterFieldsRegister)
      : RRegisterFieldsType(RRegisterFieldsRegister) {}
};

template <class ReadRRegisterFieldsRegisterType,
          class ReadRRegisterFieldsReadRRegisterFieldsType,
          class ReadRRegisterFieldsFieldType>
inline bool operator==(
    const ReadRRegisterFields<ReadRRegisterFieldsRegisterType,
                              ReadRRegisterFieldsReadRRegisterFieldsType,
                              ReadRRegisterFieldsFieldType> &LhandSide,
    const ReadRRegisterFields<ReadRRegisterFieldsRegisterType,
                              ReadRRegisterFieldsReadRRegisterFieldsType,
                              ReadRRegisterFieldsFieldType> &RhandSide) {
  return (LhandSide.R == RhandSide.R) &&
         (LhandSide.RegisterValue == RhandSide.RegisterValue);
}

template <class ReadRRegisterFieldsRegisterType,
          class ReadRRegisterFieldsReadRRegisterFieldsType,
          class ReadRRegisterFieldsFieldType>
class ReadRRegisterFields<ReadRRegisterFieldsRegisterType,
                          ReadRRegisterFieldsReadRRegisterFieldsType,
                          ReadRRegisterFieldsFieldType> {
  using RegisterType = ReadRRegisterFieldsRegisterType;
  using ReadRRegisterFieldsType = ReadRRegisterFieldsReadRRegisterFieldsType;
  using FieldType = ReadRRegisterFieldsFieldType;

protected:
  const RegisterType &R;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  const RegisterValueType RegisterValue;

  ReadRRegisterFields(const RegisterType &ReadRRegisterFieldsRegister,
                      const RegisterValueType ReadRRegisterFieldsRegisterValue)
      : R(ReadRRegisterFieldsRegister),
        RegisterValue(ReadRRegisterFieldsRegisterValue) {}

public:
  friend bool operator==<>(const ReadRRegisterFields &LhandSide,
                           const ReadRRegisterFields &RhandSide);

private:
  using FieldReadRegisterFieldType = typename FieldType::ReadRegisterFieldType;

public:
  auto read(FieldReadRegisterFieldType &F) const {
    F = FieldReadRegisterFieldType::read(this->RegisterValue);
    return ReadRRegisterFieldsType(this->R, this->RegisterValue);
  }
};

template <class ReadRRegisterFieldsRegisterType,
          class ReadRRegisterFieldsReadRRegisterFieldsType,
          class ReadRRegisterFieldsFieldType,
          class... ReadRRegisterFieldsFieldsgep1Types>
class ReadRRegisterFields
    : public ReadRRegisterFields<ReadRRegisterFieldsRegisterType,
                                 ReadRRegisterFieldsReadRRegisterFieldsType,
                                 ReadRRegisterFieldsFieldsgep1Types...> {
  using RegisterType = ReadRRegisterFieldsRegisterType;
  using ReadRRegisterFieldsType = ReadRRegisterFieldsReadRRegisterFieldsType;
  using FieldType = ReadRRegisterFieldsFieldType;
  using ReadRRegisterFieldsgep1Type =
      ReadRRegisterFields<RegisterType, ReadRRegisterFieldsType,
                          ReadRRegisterFieldsFieldsgep1Types...>;
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  ReadRRegisterFields(const RegisterType &ReadRRegisterFieldsRegister,
                      const RegisterValueType ReadRRegisterFieldsRegisterValue)
      : ReadRRegisterFieldsgep1Type(ReadRRegisterFieldsRegister,
                                    ReadRRegisterFieldsRegisterValue) {}

public:
  using ReadRRegisterFieldsgep1Type::read;

private:
  using FieldReadRegisterFieldType = typename FieldType::ReadRegisterFieldType;

public:
  auto read(FieldReadRegisterFieldType &F) const {
    F = FieldReadRegisterFieldType::read(this->RegisterValue);
    return ReadRRegisterFieldsType(this->R, this->RegisterValue);
  }
};

template <class ReadRRegisterFieldsRegisterType,
          class ReadRRegisterFieldsReadWRegisterFieldsType,
          class... ReadRRegisterFieldsFieldsTypes>
bool operator==(
    const ReadRRegisterFieldsge0<ReadRRegisterFieldsRegisterType,
                                 ReadRRegisterFieldsReadWRegisterFieldsType,
                                 ReadRRegisterFieldsFieldsTypes...> &LhandSide,
    const ReadRRegisterFieldsge0<ReadRRegisterFieldsRegisterType,
                                 ReadRRegisterFieldsReadWRegisterFieldsType,
                                 ReadRRegisterFieldsFieldsTypes...>
        &RhandSide) {
  return (static_cast<const ReadRRegisterFieldsReadWRegisterFieldsType &>(
              LhandSide) ==
          static_cast<const ReadRRegisterFieldsReadWRegisterFieldsType &>(
              RhandSide)) &&
         (static_cast<const ReadRRegisterFields<
              ReadRRegisterFieldsRegisterType,
              ReadRRegisterFieldsge0<
                  ReadRRegisterFieldsRegisterType,
                  ReadRRegisterFieldsReadWRegisterFieldsType,
                  ReadRRegisterFieldsFieldsTypes...>,
              ReadRRegisterFieldsFieldsTypes...> &>(LhandSide) ==
          static_cast<const ReadRRegisterFields<
              ReadRRegisterFieldsRegisterType,
              ReadRRegisterFieldsge0<
                  ReadRRegisterFieldsRegisterType,
                  ReadRRegisterFieldsReadWRegisterFieldsType,
                  ReadRRegisterFieldsFieldsTypes...>,
              ReadRRegisterFieldsFieldsTypes...> &>(RhandSide));
}

template <class ReadRRegisterFieldsRegisterType,
          class ReadRRegisterFieldsReadWRegisterFieldsType,
          class... ReadRRegisterFieldsFieldsTypes>
class ReadRRegisterFieldsge0
    : public ReadRRegisterFieldsReadWRegisterFieldsType,
      public ReadRRegisterFields<
          ReadRRegisterFieldsRegisterType,
          ReadRRegisterFieldsge0<ReadRRegisterFieldsRegisterType,
                                 ReadRRegisterFieldsReadWRegisterFieldsType,
                                 ReadRRegisterFieldsFieldsTypes...>,
          ReadRRegisterFieldsFieldsTypes...> {
  using RegisterType = ReadRRegisterFieldsRegisterType;
  using ReadWRegisterFieldsType = ReadRRegisterFieldsReadWRegisterFieldsType;
  using ReadRRegisterFieldsType = ReadRRegisterFields<
      RegisterType,
      ReadRRegisterFieldsge0<RegisterType, ReadWRegisterFieldsType,
                             ReadRRegisterFieldsFieldsTypes...>,
      ReadRRegisterFieldsFieldsTypes...>;

public:
  using ReadRRegisterFieldsType::read;
  using ReadWRegisterFieldsType::write;

private:
  using RegisterValueType = typename RegisterType::ValueType;

public:
  ReadRRegisterFieldsge0(
      const RegisterType &ReadRRegisterFieldsRegister,
      const RegisterValueType ReadRRegisterFieldsRegisterValue)
      : ReadWRegisterFieldsType(ReadRRegisterFieldsRegister,
                                ReadRRegisterFieldsRegisterValue),
        ReadRRegisterFieldsType(ReadRRegisterFieldsRegister,
                                ReadRRegisterFieldsRegisterValue) {}
};

template <class WRegisterFieldsRegisterType,
          bool WRegisterFieldsMightAllFieldsBeWritten,
          typename WRegisterFieldsRegisterType::ValueType
              WRegisterFieldsRegisterResetValue,
          class WRegisterFieldsFieldType,
          class... WRegisterFieldsFieldTypesgep1Types>
class WRegisterFields;
template <class IsRegisterReadableRegisterType, class = void>
class IsRegisterReadable;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteType>
class Write;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWRegisterFieldsm1Type,
          class WriteWRegisterFieldsm1FieldType>
class WriteField0;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWRegisterFieldsm1Type,
          class WriteWRegisterFieldsm1FieldType, class WriteFieldType,
          class... WriteFieldsgep1Types>
class WriteField0WRegisterFields;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1WRegisterFieldsType,
          class WriteWriteFieldslem1WRegisterFieldsFieldType>
class WriteFieldslege1;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1WRegisterFieldsType,
          class WriteWriteFieldslem1WRegisterFieldsFieldType,
          class WriteFieldType, class... WriteFieldsgep1Types>
class WriteFieldslege1WRegisterFields;

template <class WRegisterFieldsRegisterType,
          bool WRegisterFieldsMightAllFieldsBeWritten,
          typename WRegisterFieldsRegisterType::ValueType
              WRegisterFieldsRegisterResetValue,
          class WRegisterFieldsFieldType>
inline bool
operator==(const WRegisterFields<WRegisterFieldsRegisterType,
                                 WRegisterFieldsMightAllFieldsBeWritten,
                                 WRegisterFieldsRegisterResetValue,
                                 WRegisterFieldsFieldType> &LhandSide,
           const WRegisterFields<WRegisterFieldsRegisterType,
                                 WRegisterFieldsMightAllFieldsBeWritten,
                                 WRegisterFieldsRegisterResetValue,
                                 WRegisterFieldsFieldType> &RhandSide) {
  return LhandSide.R == RhandSide.R;
}

template <class WRegisterFieldsRegisterType,
          bool WRegisterFieldsMightAllFieldsBeWritten,
          typename WRegisterFieldsRegisterType::ValueType
              WRegisterFieldsRegisterResetValue,
          class WRegisterFieldsFieldType>
class WRegisterFields<
    WRegisterFieldsRegisterType, WRegisterFieldsMightAllFieldsBeWritten,
    WRegisterFieldsRegisterResetValue, WRegisterFieldsFieldType> {
  using RegisterType = WRegisterFieldsRegisterType;
  static constexpr auto MightAllFieldsBeWritten{
      WRegisterFieldsMightAllFieldsBeWritten};
  static constexpr auto RegisterResetValue{WRegisterFieldsRegisterResetValue};
  using FieldType = WRegisterFieldsFieldType;

protected:
  const RegisterType &R;

public:
  explicit WRegisterFields(const RegisterType &WRegisterFieldsRegister)
      : R(WRegisterFieldsRegister) {}

  friend bool operator==
      <>(const WRegisterFields &LhandSide, const WRegisterFields &RhandSide);

private:
  using WRegisterFieldsType =
      WRegisterFields<RegisterType, MightAllFieldsBeWritten,
                      RegisterResetValue, FieldType>;
  using WriteField0Type =
      WriteField0<RegisterType, MightAllFieldsBeWritten, RegisterResetValue,
                  WRegisterFieldsType, FieldType>;

public:
  auto write(const FieldType F) const { return WriteField0Type(this->R, F); }
};

template <class WRegisterFieldsRegisterType,
          bool WRegisterFieldsMightAllFieldsBeWritten,
          typename WRegisterFieldsRegisterType::ValueType
              WRegisterFieldsRegisterResetValue,
          class WRegisterFieldsFieldType,
          class... WRegisterFieldsFieldTypesgep1Types>
class WRegisterFields
    : public WRegisterFields<WRegisterFieldsRegisterType, false,
                             WRegisterFieldsRegisterResetValue,
                             WRegisterFieldsFieldTypesgep1Types...> {
  using RegisterType = WRegisterFieldsRegisterType;
  static constexpr auto MightAllFieldsBeWritten{
      WRegisterFieldsMightAllFieldsBeWritten};
  static constexpr auto RegisterResetValue{WRegisterFieldsRegisterResetValue};
  using FieldType = WRegisterFieldsFieldType;
  using WRegisterFieldsgep1Type =
      WRegisterFields<RegisterType, false, RegisterResetValue,
                      WRegisterFieldsFieldTypesgep1Types...>;

public:
  using WRegisterFieldsgep1Type::write;

  explicit WRegisterFields(const RegisterType &WRegisterFieldsRegister)
      : WRegisterFieldsgep1Type(WRegisterFieldsRegister) {}

private:
  using WRegisterFieldsType =
      WRegisterFields<RegisterType, MightAllFieldsBeWritten,
                      RegisterResetValue, FieldType,
                      WRegisterFieldsFieldTypesgep1Types...>;
  using WriteField0WRegisterFieldsType = WriteField0WRegisterFields<
      RegisterType, MightAllFieldsBeWritten, RegisterResetValue,
      WRegisterFieldsType, FieldType, WRegisterFieldsFieldTypesgep1Types...>;

public:
  auto write(const FieldType F) const {
    return WriteField0WRegisterFieldsType(this->R, F);
  }
};

template <class IsRegisterReadableRegisterType, class>
class IsRegisterReadable : public std::false_type {};

template <class IsRegisterReadableRegisterType>
class IsRegisterReadable<
    IsRegisterReadableRegisterType,
    decltype(std::declval<IsRegisterReadableRegisterType>().read(), void())>
    : public std::true_type {};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteType>
class Write {
  using RegisterType = WriteRegisterType;
  static constexpr auto MightAllFieldsBeWritten{WriteMightAllFieldsBeWritten};
  static constexpr auto RegisterResetValue{WriteRegisterResetValue};
  using WriteType = WriteWriteType;

protected:
  const RegisterType &R;

  explicit Write(const RegisterType &WriteRegister) : R(WriteRegister) {}

private:
  using RegisterValueType = typename RegisterType::ValueType;

public:
  void write() const {
    RegisterValueType RegisterValue;

    if constexpr (IsRegisterReadable<RegisterType>::value &&
                  !MightAllFieldsBeWritten)
      RegisterValue = this->R.read();
    else
      RegisterValue = RegisterResetValue;

    this->R.write((RegisterValue & WriteType::getInverseMask()) |
                  *static_cast<const WriteType *>(this));
  }
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWRegisterFieldsm1Type,
          class WriteWRegisterFieldsm1FieldType>
inline bool operator==(
    const WriteField0<WriteRegisterType, WriteMightAllFieldsBeWritten,
                      WriteRegisterResetValue, WriteWRegisterFieldsm1Type,
                      WriteWRegisterFieldsm1FieldType> &LhandSide,
    const WriteField0<WriteRegisterType, WriteMightAllFieldsBeWritten,
                      WriteRegisterResetValue, WriteWRegisterFieldsm1Type,
                      WriteWRegisterFieldsm1FieldType> &RhandSide) {
  return (LhandSide.R == RhandSide.R) && (LhandSide.V == RhandSide.V);
}

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWRegisterFieldsm1Type,
          class WriteWRegisterFieldsm1FieldType>
class WriteField0
    : public Write<
          WriteRegisterType, WriteMightAllFieldsBeWritten,
          WriteRegisterResetValue,
          WriteField0<WriteRegisterType, WriteMightAllFieldsBeWritten,
                      WriteRegisterResetValue, WriteWRegisterFieldsm1Type,
                      WriteWRegisterFieldsm1FieldType>> {
  using RegisterType = WriteRegisterType;
  static constexpr auto MightAllFieldsBeWritten{WriteMightAllFieldsBeWritten};
  static constexpr auto RegisterResetValue{WriteRegisterResetValue};
  using WRegisterFieldsm1Type = WriteWRegisterFieldsm1Type;
  using WRegisterFieldsm1FieldType = WriteWRegisterFieldsm1FieldType;
  using WriteField0Type =
      WriteField0<RegisterType, MightAllFieldsBeWritten, RegisterResetValue,
                  WRegisterFieldsm1Type, WRegisterFieldsm1FieldType>;
  using WriteType = Write<RegisterType, MightAllFieldsBeWritten,
                          RegisterResetValue, WriteField0Type>;
  friend WriteType;
  static constexpr auto InverseMask{~(WRegisterFieldsm1FieldType::getMask())};
  using RegisterValueType = typename RegisterType::ValueType;
  const RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  operator RegisterValueType() const { return this->V; }

public:
  WriteField0(const RegisterType &WriteRegister,
              const WRegisterFieldsm1FieldType WriteWRegisterFieldsm1Field)
      : WriteType(WriteRegister), V(WriteWRegisterFieldsm1Field) {}

  friend bool operator==
      <>(const WriteField0 &LhandSide, const WriteField0 &RhandSide);
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWRegisterFieldsm1Type,
          class WriteWRegisterFieldsm1FieldType, class WriteFieldType>
class WriteField0WRegisterFields<
    WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
    WriteWRegisterFieldsm1Type, WriteWRegisterFieldsm1FieldType,
    WriteFieldType>
    : public WriteField0<WriteRegisterType, false, WriteRegisterResetValue,
                         WriteWRegisterFieldsm1Type,
                         WriteWRegisterFieldsm1FieldType> {
  using RegisterType = WriteRegisterType;
  static constexpr auto MightAllFieldsBeWritten{WriteMightAllFieldsBeWritten};
  static constexpr auto RegisterResetValue{WriteRegisterResetValue};
  using WRegisterFieldsm1Type = WriteWRegisterFieldsm1Type;
  using WRegisterFieldsm1FieldType = WriteWRegisterFieldsm1FieldType;
  using FieldType = WriteFieldType;
  using WriteField0WRegisterFieldsType =
      WriteField0WRegisterFields<RegisterType, MightAllFieldsBeWritten,
                                 RegisterResetValue, WRegisterFieldsm1Type,
                                 WRegisterFieldsm1FieldType, FieldType>;
  template <bool MAFBW>
  using WriteFieldsle1Type =
      WriteFieldslege1<RegisterType, MAFBW, RegisterResetValue,
                       WriteField0WRegisterFieldsType, FieldType>;
  friend WriteFieldsle1Type<MightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0Type =
      WriteField0<RegisterType, false, RegisterResetValue,
                  WRegisterFieldsm1Type, WRegisterFieldsm1FieldType>;

protected:
  using WriteField0Type::getInverseMask;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  using WriteField0Type::operator RegisterValueType;

public:
  using WriteField0Type::write;

  WriteField0WRegisterFields(
      const RegisterType &WriteRegister,
      const WRegisterFieldsm1FieldType WriteWRegisterFieldsm1Field)
      : WriteField0Type(WriteRegister, WriteWRegisterFieldsm1Field) {}

  auto write(const FieldType F) const {
    return WriteFieldsle1Type<MightAllFieldsBeWritten>(this->R, *this, F);
  }
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWRegisterFieldsm1Type,
          class WriteWRegisterFieldsm1FieldType, class WriteFieldType,
          class... WriteFieldsgep1Types>
class WriteField0WRegisterFields
    : public WriteField0WRegisterFields<
          WriteRegisterType, false, WriteRegisterResetValue,
          WriteWRegisterFieldsm1Type, WriteWRegisterFieldsm1FieldType,
          WriteFieldsgep1Types...> {
  using RegisterType = WriteRegisterType;
  static constexpr auto MightAllFieldsBeWritten{WriteMightAllFieldsBeWritten};
  static constexpr auto RegisterResetValue{WriteRegisterResetValue};
  using WRegisterFieldsm1Type = WriteWRegisterFieldsm1Type;
  using WRegisterFieldsm1FieldType = WriteWRegisterFieldsm1FieldType;
  using FieldType = WriteFieldType;
  using WriteField0WRegisterFieldsType =
      WriteField0WRegisterFields<RegisterType, WriteMightAllFieldsBeWritten,
                                 RegisterResetValue, WRegisterFieldsm1Type,
                                 WRegisterFieldsm1FieldType, FieldType,
                                 WriteFieldsgep1Types...>;
  template <bool MAFBW>
  using WriteFieldsle1Type =
      WriteFieldslege1<RegisterType, MAFBW, RegisterResetValue,
                       WriteField0WRegisterFieldsType, FieldType>;
  friend WriteFieldsle1Type<WriteMightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0WRegisterFieldsgep1Type = WriteField0WRegisterFields<
      RegisterType, false, RegisterResetValue, WRegisterFieldsm1Type,
      WRegisterFieldsm1FieldType, WriteFieldsgep1Types...>;

protected:
  using WriteField0WRegisterFieldsgep1Type::getInverseMask;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  using WriteField0WRegisterFieldsgep1Type::operator RegisterValueType;

public:
  using WriteField0WRegisterFieldsgep1Type::write;

  WriteField0WRegisterFields(
      const RegisterType &WriteRegister,
      const WRegisterFieldsm1FieldType WriteWRegisterFieldsm1Field)
      : WriteField0WRegisterFieldsgep1Type(WriteRegister,
                                           WriteWRegisterFieldsm1Field) {}

private:
  using WriteFieldsle1WRegisterFieldsType = WriteFieldslege1WRegisterFields<
      RegisterType, WriteMightAllFieldsBeWritten, RegisterResetValue,
      WriteField0WRegisterFieldsType, FieldType, WriteFieldsgep1Types...>;

public:
  auto write(const FieldType F) const {
    return WriteFieldsle1WRegisterFieldsType(this->R, *this, F);
  }
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1WRegisterFieldsType,
          class WriteWriteFieldslem1WRegisterFieldsFieldType>
inline bool operator==(
    const WriteFieldslege1<
        WriteRegisterType, WriteMightAllFieldsBeWritten,
        WriteRegisterResetValue, WriteWriteFieldslem1WRegisterFieldsType,
        WriteWriteFieldslem1WRegisterFieldsFieldType> &LhandSide,
    const WriteFieldslege1<
        WriteRegisterType, WriteMightAllFieldsBeWritten,
        WriteRegisterResetValue, WriteWriteFieldslem1WRegisterFieldsType,
        WriteWriteFieldslem1WRegisterFieldsFieldType> &RhandSide) {
  return (LhandSide.R == RhandSide.R) &&
         (LhandSide.WriteFieldslem1WRegisterFields ==
          RhandSide.WriteFieldslem1WRegisterFields) &&
         (LhandSide.V == RhandSide.V);
}

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1WRegisterFieldsType,
          class WriteWriteFieldslem1WRegisterFieldsFieldType>
class WriteFieldslege1
    : public Write<
          WriteRegisterType, WriteMightAllFieldsBeWritten,
          WriteRegisterResetValue,
          WriteFieldslege1<WriteRegisterType, WriteMightAllFieldsBeWritten,
                           WriteRegisterResetValue,
                           WriteWriteFieldslem1WRegisterFieldsType,
                           WriteWriteFieldslem1WRegisterFieldsFieldType>> {
  using RegisterType = WriteRegisterType;
  static constexpr auto MightAllFieldsBeWritten{WriteMightAllFieldsBeWritten};
  static constexpr auto RegisterResetValue{WriteRegisterResetValue};
  using WriteFieldslem1WRegisterFieldsType =
      WriteWriteFieldslem1WRegisterFieldsType;
  using WriteFieldslem1WRegisterFieldsFieldType =
      WriteWriteFieldslem1WRegisterFieldsFieldType;
  using WriteFieldslege1Type =
      WriteFieldslege1<RegisterType, MightAllFieldsBeWritten,
                       RegisterResetValue, WriteFieldslem1WRegisterFieldsType,
                       WriteFieldslem1WRegisterFieldsFieldType>;
  using WriteType = Write<RegisterType, MightAllFieldsBeWritten,
                          RegisterResetValue, WriteFieldslege1Type>;
  friend WriteType;
  static constexpr auto InverseMask{
      ~(WriteFieldslem1WRegisterFieldsFieldType::getMask()) &
      WriteFieldslem1WRegisterFieldsType::getInverseMask()};

protected:
  const WriteFieldslem1WRegisterFieldsType &WriteFieldslem1WRegisterFields;

private:
  using RegisterValueType = typename RegisterType::ValueType;
  RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  operator RegisterValueType() const { return this->V; }

public:
  WriteFieldslege1(const RegisterType &WriteRegister,
                   const WriteFieldslem1WRegisterFieldsType
                       &WriteWriteFieldslem1WRegisterFields,
                   const WriteFieldslem1WRegisterFieldsFieldType
                       WriteWriteFieldslem1WRegisterFieldsField)
      : WriteType(WriteRegister),
        WriteFieldslem1WRegisterFields(WriteWriteFieldslem1WRegisterFields),
        V(WriteWriteFieldslem1WRegisterFieldsField |
          WriteWriteFieldslem1WRegisterFields) {}

  friend bool operator==
      <>(const WriteFieldslege1 &LhandSide, const WriteFieldslege1 &RhandSide);
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1WRegisterFieldsType,
          class WriteWriteFieldslem1WRegisterFieldsFieldType,
          class WriteFieldType>
class WriteFieldslege1WRegisterFields<
    WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
    WriteWriteFieldslem1WRegisterFieldsType,
    WriteWriteFieldslem1WRegisterFieldsFieldType, WriteFieldType>
    : public WriteFieldslege1<WriteRegisterType, false,
                              WriteRegisterResetValue,
                              WriteWriteFieldslem1WRegisterFieldsType,
                              WriteWriteFieldslem1WRegisterFieldsFieldType> {
  using RegisterType = WriteRegisterType;
  static constexpr auto MightAllFieldsBeWritten{WriteMightAllFieldsBeWritten};
  static constexpr auto RegisterResetValue{WriteRegisterResetValue};
  using WriteFieldslem1WRegisterFieldsType =
      WriteWriteFieldslem1WRegisterFieldsType;
  using WriteFieldslem1WRegisterFieldsFieldType =
      WriteWriteFieldslem1WRegisterFieldsFieldType;
  using FieldType = WriteFieldType;
  using WriteFieldslege1WRegisterFieldsType = WriteFieldslege1WRegisterFields<
      RegisterType, MightAllFieldsBeWritten, RegisterResetValue,
      WriteFieldslem1WRegisterFieldsType,
      WriteFieldslem1WRegisterFieldsFieldType, FieldType>;
  template <bool MAFBW>
  using WriteFieldslep1Type =
      WriteFieldslege1<RegisterType, MAFBW, RegisterResetValue,
                       WriteFieldslege1WRegisterFieldsType, FieldType>;
  friend WriteFieldslep1Type<MightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1Type =
      WriteFieldslege1<RegisterType, false, RegisterResetValue,
                       WriteFieldslem1WRegisterFieldsType,
                       WriteFieldslem1WRegisterFieldsFieldType>;

protected:
  using WriteFieldslege1Type::getInverseMask;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  using WriteFieldslege1Type::operator RegisterValueType;

public:
  using WriteFieldslege1Type::write;

  WriteFieldslege1WRegisterFields(const RegisterType &WriteRegister,
                                  const WriteFieldslem1WRegisterFieldsType
                                      &WriteWriteFieldslem1WRegisterFields,
                                  const WriteFieldslem1WRegisterFieldsFieldType
                                      WriteWriteFieldslem1WRegisterFieldsField)
      : WriteFieldslege1Type(WriteRegister,
                             WriteWriteFieldslem1WRegisterFields,
                             WriteWriteFieldslem1WRegisterFieldsField) {}

  auto write(const FieldType F) const {
    return WriteFieldslep1Type<MightAllFieldsBeWritten>(this->R, *this, F);
  }
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1WRegisterFieldsType,
          class WriteWriteFieldslem1WRegisterFieldsFieldType,
          class WriteFieldType, class... WriteFieldsgep1Types>
class WriteFieldslege1WRegisterFields
    : public WriteFieldslege1WRegisterFields<
          WriteRegisterType, false, WriteRegisterResetValue,
          WriteWriteFieldslem1WRegisterFieldsType,
          WriteWriteFieldslem1WRegisterFieldsFieldType,
          WriteFieldsgep1Types...> {
  using RegisterType = WriteRegisterType;
  static constexpr auto MightAllFieldsBeWritten{WriteMightAllFieldsBeWritten};
  static constexpr auto RegisterResetValue{WriteRegisterResetValue};
  using WriteFieldslem1WRegisterFieldsType =
      WriteWriteFieldslem1WRegisterFieldsType;
  using WriteFieldslem1WRegisterFieldsFieldType =
      WriteWriteFieldslem1WRegisterFieldsFieldType;
  using FieldType = WriteFieldType;
  using WriteFieldslege1WRegisterFieldsType =
      WriteFieldslege1WRegisterFields<RegisterType, MightAllFieldsBeWritten,
                                      RegisterResetValue,
                                      WriteFieldslem1WRegisterFieldsType,
                                      WriteFieldslem1WRegisterFieldsFieldType,
                                      FieldType, WriteFieldsgep1Types...>;
  template <bool MAFBW>
  using WriteFieldslep1Type =
      WriteFieldslege1<RegisterType, MAFBW, RegisterResetValue,
                       WriteFieldslege1WRegisterFieldsType, FieldType>;
  friend WriteFieldslep1Type<MightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1WRegisterFieldsgep1Type =
      WriteFieldslege1WRegisterFields<RegisterType, false, RegisterResetValue,
                                      WriteFieldslem1WRegisterFieldsType,
                                      WriteFieldslem1WRegisterFieldsFieldType,
                                      WriteFieldsgep1Types...>;

protected:
  using WriteFieldslege1WRegisterFieldsgep1Type::getInverseMask;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  using WriteFieldslege1WRegisterFieldsgep1Type::operator RegisterValueType;

public:
  using WriteFieldslege1WRegisterFieldsgep1Type::write;

  WriteFieldslege1WRegisterFields(const RegisterType &WriteRegister,
                                  const WriteFieldslem1WRegisterFieldsType
                                      &WriteWriteFieldslem1WRegisterFields,
                                  const WriteFieldslem1WRegisterFieldsFieldType
                                      WriteWriteFieldslem1WRegisterFieldsField)
      : WriteFieldslege1WRegisterFieldsgep1Type(
            WriteRegister, WriteWriteFieldslem1WRegisterFields,
            WriteWriteFieldslem1WRegisterFieldsField) {}

private:
  using WriteFieldslep1WRegisterFieldsType = WriteFieldslege1WRegisterFields<
      RegisterType, MightAllFieldsBeWritten, RegisterResetValue,
      WriteFieldslege1WRegisterFieldsType, FieldType, WriteFieldsgep1Types...>;

public:
  auto write(const FieldType F) const {
    return WriteFieldslep1WRegisterFieldsType(this->R, *this, F);
  }
};

template <class ReadWRegisterFieldsRegisterType,
          class ReadWRegisterFieldsFieldType,
          class... ReadWRegisterFieldsFieldTypesgep1Types>
class ReadWRegisterFields;
template <class ReadWriteRegisterType, class ReadWriteReadWriteType>
class ReadWrite;
template <class ReadWriteRegisterType,
          class ReadWriteReadWRegisterFieldsm1Type,
          class ReadWriteReadWRegisterFieldsm1FieldType>
class ReadWriteField0;
template <class ReadWriteRegisterType,
          class ReadWriteReadWRegisterFieldsm1Type,
          class ReadWriteReadWRegisterFieldsm1FieldType,
          class ReadWriteFieldType, class... ReadWriteFieldsgep1Types>
class ReadWriteField0WRegisterFields;
template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType>
class ReadWriteFieldslege1;
template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType,
          class ReadWriteFieldType, class... ReadWriteFieldsgep1Types>
class ReadWriteFieldslege1WRegisterFields;

template <class ReadWRegisterFieldsRegisterType,
          class ReadWRegisterFieldsFieldType>
inline bool operator==(
    const ReadWRegisterFields<ReadWRegisterFieldsRegisterType,
                              ReadWRegisterFieldsFieldType> &LhandSide,
    const ReadWRegisterFields<ReadWRegisterFieldsRegisterType,
                              ReadWRegisterFieldsFieldType> &RhandSide) {
  return (LhandSide.R == RhandSide.R) &&
         (LhandSide.RegisterValue == RhandSide.RegisterValue);
}

template <class ReadWRegisterFieldsRegisterType,
          class ReadWRegisterFieldsFieldType>
class ReadWRegisterFields<ReadWRegisterFieldsRegisterType,
                          ReadWRegisterFieldsFieldType> {
  using RegisterType = ReadWRegisterFieldsRegisterType;
  using FieldType = ReadWRegisterFieldsFieldType;

protected:
  const RegisterType &R;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  const RegisterValueType RegisterValue;

public:
  ReadWRegisterFields(const RegisterType &ReadWRegisterFieldsRegister,
                      const RegisterValueType ReadWRegisterFieldsRegisterValue)
      : R(ReadWRegisterFieldsRegister),
        RegisterValue(ReadWRegisterFieldsRegisterValue) {}

  friend bool operator==<>(const ReadWRegisterFields &LhandSide,
                           const ReadWRegisterFields &RhandSide);

private:
  using ReadWRegisterFieldsType = ReadWRegisterFields<RegisterType, FieldType>;
  using ReadWriteField0Type =
      ReadWriteField0<RegisterType, ReadWRegisterFieldsType, FieldType>;

public:
  auto write(const FieldType F) const {
    return ReadWriteField0Type(this->R, this->RegisterValue, F);
  }
};

template <class ReadWRegisterFieldsRegisterType,
          class ReadWRegisterFieldsFieldType,
          class... ReadWRegisterFieldsFieldTypesgep1Types>
class ReadWRegisterFields
    : public ReadWRegisterFields<ReadWRegisterFieldsRegisterType,
                                 ReadWRegisterFieldsFieldTypesgep1Types...> {
  using RegisterType = ReadWRegisterFieldsRegisterType;
  using FieldType = ReadWRegisterFieldsFieldType;
  using ReadWRegisterFieldsgep1Type =
      ReadWRegisterFields<RegisterType,
                          ReadWRegisterFieldsFieldTypesgep1Types...>;

public:
  using ReadWRegisterFieldsgep1Type::write;

private:
  using RegisterValueType = typename RegisterType::ValueType;

public:
  ReadWRegisterFields(const RegisterType &ReadWRegisterFieldsRegister,
                      const RegisterValueType ReadWRegisterFieldsRegisterValue)
      : ReadWRegisterFieldsgep1Type(ReadWRegisterFieldsRegister,
                                    ReadWRegisterFieldsRegisterValue) {}

private:
  using ReadWRegisterFieldsType =
      ReadWRegisterFields<RegisterType, FieldType,
                          ReadWRegisterFieldsFieldTypesgep1Types...>;
  using ReadWriteField0WRegisterFieldsType = ReadWriteField0WRegisterFields<
      RegisterType, ReadWRegisterFieldsType, FieldType,
      ReadWRegisterFieldsFieldTypesgep1Types...>;

public:
  auto write(const FieldType F) const {
    return ReadWriteField0WRegisterFieldsType(this->R, this->RegisterValue, F);
  }
};

template <class ReadWriteRegisterType, class ReadWriteReadWriteType>
class ReadWrite {
  using RegisterType = ReadWriteRegisterType;
  using ReadWriteType = ReadWriteReadWriteType;

protected:
  const RegisterType &R;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  const RegisterValueType RegisterValue;

public:
  ReadWrite(const RegisterType &ReadWriteRegister,
            const RegisterValueType ReadWriteRegisterValue)
      : R(ReadWriteRegister), RegisterValue(ReadWriteRegisterValue) {}

  void write() const {
    this->R.write((this->RegisterValue & ReadWriteType::getInverseMask()) |
                  *static_cast<const ReadWriteType *>(this));
  }
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWRegisterFieldsm1Type,
          class ReadWriteReadWRegisterFieldsm1FieldType>
inline bool operator==(
    const ReadWriteField0<ReadWriteRegisterType,
                          ReadWriteReadWRegisterFieldsm1Type,
                          ReadWriteReadWRegisterFieldsm1FieldType> &LhandSide,
    const ReadWriteField0<
        ReadWriteRegisterType, ReadWriteReadWRegisterFieldsm1Type,
        ReadWriteReadWRegisterFieldsm1FieldType> &RhandSide) {
  return (LhandSide.R == RhandSide.R) &&
         (LhandSide.RegisterValue == RhandSide.RegisterValue) &&
         (LhandSide.V == RhandSide.V);
}

template <class ReadWriteRegisterType,
          class ReadWriteReadWRegisterFieldsm1Type,
          class ReadWriteReadWRegisterFieldsm1FieldType>
class ReadWriteField0
    : public ReadWrite<
          ReadWriteRegisterType,
          ReadWriteField0<ReadWriteRegisterType,
                          ReadWriteReadWRegisterFieldsm1Type,
                          ReadWriteReadWRegisterFieldsm1FieldType>> {
  using RegisterType = ReadWriteRegisterType;
  using ReadWRegisterFieldsm1Type = ReadWriteReadWRegisterFieldsm1Type;
  using ReadWRegisterFieldsm1FieldType =
      ReadWriteReadWRegisterFieldsm1FieldType;
  using ReadWriteField0Type =
      ReadWriteField0<RegisterType, ReadWRegisterFieldsm1Type,
                      ReadWRegisterFieldsm1FieldType>;
  using ReadWriteType = ReadWrite<RegisterType, ReadWriteField0Type>;
  friend ReadWriteType;
  static constexpr auto InverseMask{
      ~(ReadWRegisterFieldsm1FieldType::getMask())};
  using RegisterValueType = typename RegisterType::ValueType;
  const RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  operator RegisterValueType() const { return this->V; }

public:
  ReadWriteField0(
      const RegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWRegisterFieldsm1FieldType ReadWriteReadWRegisterFieldsm1Field)
      : ReadWriteType(ReadWriteRegister, ReadWriteRegisterValue),
        V(ReadWriteReadWRegisterFieldsm1Field) {}

  friend bool operator==
      <>(const ReadWriteField0 &LhandSide, const ReadWriteField0 &RhandSide);
};

template <
    class ReadWriteRegisterType, class ReadWriteReadWRegisterFieldsm1Type,
    class ReadWriteReadWRegisterFieldsm1FieldType, class ReadWriteFieldType>
class ReadWriteField0WRegisterFields<
    ReadWriteRegisterType, ReadWriteReadWRegisterFieldsm1Type,
    ReadWriteReadWRegisterFieldsm1FieldType, ReadWriteFieldType>
    : public ReadWriteField0<ReadWriteRegisterType,
                             ReadWriteReadWRegisterFieldsm1Type,
                             ReadWriteReadWRegisterFieldsm1FieldType> {
  using RegisterType = ReadWriteRegisterType;
  using ReadWRegisterFieldsm1Type = ReadWriteReadWRegisterFieldsm1Type;
  using ReadWRegisterFieldsm1FieldType =
      ReadWriteReadWRegisterFieldsm1FieldType;
  using FieldType = ReadWriteFieldType;
  using ReadWriteField0WRegisterFieldsType =
      ReadWriteField0WRegisterFields<RegisterType, ReadWRegisterFieldsm1Type,
                                     ReadWRegisterFieldsm1FieldType,
                                     FieldType>;
  using ReadWriteFieldsle1Type =
      ReadWriteFieldslege1<RegisterType, ReadWriteField0WRegisterFieldsType,
                           FieldType>;
  friend ReadWriteFieldsle1Type;
  using ReadWriteField0Type =
      ReadWriteField0<RegisterType, ReadWRegisterFieldsm1Type,
                      ReadWRegisterFieldsm1FieldType>;

protected:
  using ReadWriteField0Type::getInverseMask;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  using ReadWriteField0Type::operator RegisterValueType;

public:
  using ReadWriteField0Type::write;

  ReadWriteField0WRegisterFields(
      const RegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWRegisterFieldsm1FieldType ReadWriteReadWRegisterFieldsm1Field)
      : ReadWriteField0Type(ReadWriteRegister, ReadWriteRegisterValue,
                            ReadWriteReadWRegisterFieldsm1Field) {}

  auto write(const FieldType F) const {
    return ReadWriteFieldsle1Type(this->R, this->RegisterValue, *this, F);
  }
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWRegisterFieldsm1Type,
          class ReadWriteReadWRegisterFieldsm1FieldType,
          class ReadWriteFieldType, class... ReadWriteFieldsgep1Types>
class ReadWriteField0WRegisterFields
    : public ReadWriteField0WRegisterFields<
          ReadWriteRegisterType, ReadWriteReadWRegisterFieldsm1Type,
          ReadWriteReadWRegisterFieldsm1FieldType,
          ReadWriteFieldsgep1Types...> {
  using RegisterType = ReadWriteRegisterType;
  using ReadWRegisterFieldsm1Type = ReadWriteReadWRegisterFieldsm1Type;
  using ReadWRegisterFieldsm1FieldType =
      ReadWriteReadWRegisterFieldsm1FieldType;
  using FieldType = ReadWriteFieldType;
  using ReadWriteField0WRegisterFieldsType =
      ReadWriteField0WRegisterFields<RegisterType, ReadWRegisterFieldsm1Type,
                                     ReadWRegisterFieldsm1FieldType, FieldType,
                                     ReadWriteFieldsgep1Types...>;
  friend ReadWriteFieldslege1<RegisterType, ReadWriteField0WRegisterFieldsType,
                              FieldType>;
  using ReadWriteField0WRegisterFieldsgep1Type =
      ReadWriteField0WRegisterFields<RegisterType, ReadWRegisterFieldsm1Type,
                                     ReadWRegisterFieldsm1FieldType,
                                     ReadWriteFieldsgep1Types...>;

protected:
  using ReadWriteField0WRegisterFieldsgep1Type::getInverseMask;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  using ReadWriteField0WRegisterFieldsgep1Type::operator RegisterValueType;

public:
  using ReadWriteField0WRegisterFieldsgep1Type::write;

  ReadWriteField0WRegisterFields(
      const RegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWRegisterFieldsm1FieldType ReadWriteReadWRegisterFieldsm1Field)
      : ReadWriteField0WRegisterFieldsgep1Type(
            ReadWriteRegister, ReadWriteRegisterValue,
            ReadWriteReadWRegisterFieldsm1Field) {}

private:
  using ReadWriteFieldsle1WRegisterFieldsType =
      ReadWriteFieldslege1WRegisterFields<
          RegisterType, ReadWriteField0WRegisterFieldsType, FieldType,
          ReadWriteFieldsgep1Types...>;

public:
  auto write(const FieldType F) const {
    return ReadWriteFieldsle1WRegisterFieldsType(this->R, this->RegisterValue,
                                                 *this, F);
  }
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType>
inline bool operator==(
    const ReadWriteFieldslege1<
        ReadWriteRegisterType, ReadWriteReadWriteFieldslem1WRegisterFieldsType,
        ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType> &LhandSide,
    const ReadWriteFieldslege1<
        ReadWriteRegisterType, ReadWriteReadWriteFieldslem1WRegisterFieldsType,
        ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType> &RhandSide) {
  return (LhandSide.R == RhandSide.R) &&
         (LhandSide.RegisterValue == RhandSide.RegisterValue) &&
         (LhandSide.ReadWriteFieldslem1WRegisterFields ==
          RhandSide.ReadWriteFieldslem1WRegisterFields) &&
         (LhandSide.V == RhandSide.V);
}

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType>
class ReadWriteFieldslege1
    : public ReadWrite<
          ReadWriteRegisterType,
          ReadWriteFieldslege1<
              ReadWriteRegisterType,
              ReadWriteReadWriteFieldslem1WRegisterFieldsType,
              ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType>> {
  using RegisterType = ReadWriteRegisterType;
  using ReadWriteFieldslem1WRegisterFieldsType =
      ReadWriteReadWriteFieldslem1WRegisterFieldsType;
  using ReadWriteFieldslem1WRegisterFieldsFieldType =
      ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType;
  using ReadWriteFieldslege1Type =
      ReadWriteFieldslege1<RegisterType,
                           ReadWriteFieldslem1WRegisterFieldsType,
                           ReadWriteFieldslem1WRegisterFieldsFieldType>;
  using ReadWriteType = ReadWrite<RegisterType, ReadWriteFieldslege1Type>;
  friend ReadWriteType;
  static constexpr auto InverseMask{
      ~(ReadWriteFieldslem1WRegisterFieldsFieldType::getMask()) &
      ReadWriteFieldslem1WRegisterFieldsType::getInverseMask()};

protected:
  const ReadWriteFieldslem1WRegisterFieldsType
      &ReadWriteFieldslem1WRegisterFields;

private:
  using RegisterValueType = typename RegisterType::ValueType;
  const RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  operator RegisterValueType() const { return this->V; }

public:
  ReadWriteFieldslege1(const RegisterType &ReadWriteRegister,
                       const RegisterValueType ReadWriteRegisterValue,
                       const ReadWriteFieldslem1WRegisterFieldsType
                           &ReadWriteReadWriteFieldslem1WRegisterFields,
                       const ReadWriteFieldslem1WRegisterFieldsFieldType
                           ReadWriteReadWriteFieldslem1WRegisterFieldsField)
      : ReadWriteType(ReadWriteRegister, ReadWriteRegisterValue),
        ReadWriteFieldslem1WRegisterFields(
            ReadWriteReadWriteFieldslem1WRegisterFields),
        V(ReadWriteReadWriteFieldslem1WRegisterFieldsField |
          ReadWriteReadWriteFieldslem1WRegisterFields) {}

  friend bool operator==<>(const ReadWriteFieldslege1 &LhandSide,
                           const ReadWriteFieldslege1 &RhandSide);
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType,
          class ReadWriteFieldType>
class ReadWriteFieldslege1WRegisterFields<
    ReadWriteRegisterType, ReadWriteReadWriteFieldslem1WRegisterFieldsType,
    ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType, ReadWriteFieldType>
    : public ReadWriteFieldslege1<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType> {
  using RegisterType = ReadWriteRegisterType;
  using ReadWriteFieldslem1WRegisterFieldsType =
      ReadWriteReadWriteFieldslem1WRegisterFieldsType;
  using ReadWriteFieldslem1WRegisterFieldsFieldType =
      ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType;
  using FieldType = ReadWriteFieldType;
  using ReadWriteFieldslege1WRegisterFieldsType =
      ReadWriteFieldslege1WRegisterFields<
          RegisterType, ReadWriteFieldslem1WRegisterFieldsType,
          ReadWriteFieldslem1WRegisterFieldsFieldType, FieldType>;
  using ReadWriteFieldslep1Type =
      ReadWriteFieldslege1<RegisterType,
                           ReadWriteFieldslege1WRegisterFieldsType, FieldType>;
  friend ReadWriteFieldslep1Type;
  using ReadWriteFieldslege1Type =
      ReadWriteFieldslege1<RegisterType,
                           ReadWriteFieldslem1WRegisterFieldsType,
                           ReadWriteFieldslem1WRegisterFieldsFieldType>;

protected:
  using ReadWriteFieldslege1Type::getInverseMask;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  using ReadWriteFieldslege1Type::operator RegisterValueType;

public:
  using ReadWriteFieldslege1Type::write;

  ReadWriteFieldslege1WRegisterFields(
      const RegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteFieldslem1WRegisterFieldsType
          &ReadWriteReadWriteFieldslem1WRegisterFields,
      const ReadWriteFieldslem1WRegisterFieldsFieldType
          ReadWriteReadWriteFieldslem1WRegisterFieldsField)
      : ReadWriteFieldslege1Type(
            ReadWriteRegister, ReadWriteRegisterValue,
            ReadWriteReadWriteFieldslem1WRegisterFields,
            ReadWriteReadWriteFieldslem1WRegisterFieldsField) {}

  auto write(const FieldType F) const {
    return ReadWriteFieldslep1Type(this->R, this->RegisterValue, *this, F);
  }
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          class ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType,
          class ReadWriteFieldType, class... ReadWriteFieldsgep1Types>
class ReadWriteFieldslege1WRegisterFields
    : public ReadWriteFieldslege1WRegisterFields<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType,
          ReadWriteFieldsgep1Types...> {
  using RegisterType = ReadWriteRegisterType;
  using ReadWriteFieldslem1WRegisterFieldsType =
      ReadWriteReadWriteFieldslem1WRegisterFieldsType;
  using ReadWriteFieldslem1WRegisterFieldsFieldType =
      ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType;
  using FieldType = ReadWriteFieldType;
  using ReadWriteFieldslege1WRegisterFieldsType =
      ReadWriteFieldslege1WRegisterFields<
          RegisterType, ReadWriteFieldslem1WRegisterFieldsType,
          ReadWriteFieldslem1WRegisterFieldsFieldType, FieldType,
          ReadWriteFieldsgep1Types...>;
  friend ReadWriteFieldslege1<
      RegisterType, ReadWriteFieldslege1WRegisterFieldsType, FieldType>;
  using ReadWriteFieldslege1WRegisterFieldsgep1Type =
      ReadWriteFieldslege1WRegisterFields<
          RegisterType, ReadWriteFieldslem1WRegisterFieldsType,
          ReadWriteFieldslem1WRegisterFieldsFieldType,
          ReadWriteFieldsgep1Types...>;

protected:
  using ReadWriteFieldslege1WRegisterFieldsgep1Type::getInverseMask;

private:
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  using ReadWriteFieldslege1WRegisterFieldsgep1Type::
  operator RegisterValueType;

public:
  using ReadWriteFieldslege1WRegisterFieldsgep1Type::write;

  ReadWriteFieldslege1WRegisterFields(
      const RegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteFieldslem1WRegisterFieldsType
          &ReadWriteReadWriteFieldslem1WRegisterFields,
      const ReadWriteFieldslem1WRegisterFieldsFieldType
          ReadWriteReadWriteFieldslem1WRegisterFieldsField)
      : ReadWriteFieldslege1WRegisterFieldsgep1Type(
            ReadWriteRegister, ReadWriteRegisterValue,
            ReadWriteReadWriteFieldslem1WRegisterFields,
            ReadWriteReadWriteFieldslem1WRegisterFieldsField) {}

private:
  using ReadWriteFieldslep1WRegisterFieldsType =
      ReadWriteFieldslege1WRegisterFields<
          RegisterType, ReadWriteFieldslege1WRegisterFieldsType, FieldType,
          ReadWriteFieldsgep1Types...>;

public:
  auto write(const FieldType F) const {
    return ReadWriteFieldslep1WRegisterFieldsType(this->R, this->RegisterValue,
                                                  *this, F);
  }
};

} // namespace detail

namespace detail {

template <class ReadRegisterType, class... ReadRegisterFieldsTypes> class Read;

template <class ReadRegisterType, class... ReadRegisterFieldsTypes>
class Read : public ReadWRegisterFields<ReadRegisterType,
                                        ReadRegisterFieldsTypes...> {
  using ReadWRegisterFieldsType =
      ReadWRegisterFields<ReadRegisterType, ReadRegisterFieldsTypes...>;

public:
  using ReadWRegisterFieldsType::write;

  explicit Read(const ReadRegisterType &ReadRegister)
      : ReadWRegisterFieldsType(ReadRegister, ReadRegister.read()) {}
};

} // namespace detail

template <class RegisterRegisterType,
          typename RegisterRegisterType::ValueType RegisterResetValue,
          class... RegisterFieldsTypes>
class Register
    : public detail::RRegisterFieldsge0<
          RegisterRegisterType,
          detail::ReadWRegisterFields<RegisterRegisterType,
                                      RegisterFieldsTypes...>,
          RegisterFieldsTypes...>,
      detail::WRegisterFields<RegisterRegisterType, true, RegisterResetValue,
                              RegisterFieldsTypes...> {
public:
  using RegisterType = RegisterRegisterType;
  static constexpr auto ResetValue{RegisterResetValue};

private:
  const RegisterType &R;
  using RRegisterFieldsType = detail::RRegisterFieldsge0<
      RegisterType,
      detail::ReadWRegisterFields<RegisterType, RegisterFieldsTypes...>,
      RegisterFieldsTypes...>;

public:
  using RRegisterFieldsType::read;

private:
  using WRegisterFieldsType =
      detail::WRegisterFields<RegisterType, true, ResetValue,
                              RegisterFieldsTypes...>;

public:
  using WRegisterFieldsType::write;

  Register(const RegisterType &RegisterRegister)
      : RRegisterFieldsType(RegisterRegister),
        WRegisterFieldsType(RegisterRegister), R(RegisterRegister) {}

  auto read() const {
    return detail::Read<RegisterType, RegisterFieldsTypes...>(this->R);
  }
};

} // namespace tiva

#endif // TIVA_REGISTER_REGISTER_H
