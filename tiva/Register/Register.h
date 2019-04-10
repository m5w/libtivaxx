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
class RRegisterFields<RRegisterFieldsRegisterType,
                      RRegisterFieldsReadRRegisterFieldsType,
                      RRegisterFieldsFieldType> {
  using RegisterType = RRegisterFieldsRegisterType;
  using ReadRRegisterFieldsType = RRegisterFieldsReadRRegisterFieldsType;
  using FieldType = RRegisterFieldsFieldType;

protected:
  const RegisterType &R;

public:
  explicit RRegisterFields(const RegisterType &RRegisterFieldsRegister)
      : R(RRegisterFieldsRegister) {}

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

public:
  using RRegisterFieldsgep1Type::read;

  explicit RRegisterFields(const RegisterType &RRegisterFieldsRegister)
      : RRegisterFieldsgep1Type(RRegisterFieldsRegister) {}

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
bool operator==(
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
  const RegisterType &R;
  using RegisterValueType = typename RegisterType::ValueType;

protected:
  const RegisterValueType RegisterValue;

public:
  explicit ReadRRegisterFields(
      const RegisterType &ReadRRegisterFieldsRegister,
      const RegisterValueType ReadRRegisterFieldsRegisterValue)
      : R(ReadRRegisterFieldsRegister),
        RegisterValue(ReadRRegisterFieldsRegisterValue) {}

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

public:
  using ReadRRegisterFieldsgep1Type::read;

private:
  using RegisterValueType = typename RegisterType::ValueType;

public:
  explicit ReadRRegisterFields(
      const RegisterType &ReadRRegisterFieldsRegister,
      const RegisterValueType ReadRRegisterFieldsRegisterValue)
      : ReadRRegisterFieldsgep1Type(ReadRRegisterFieldsRegister,
                                    ReadRRegisterFieldsRegisterValue) {}

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
  explicit ReadRRegisterFieldsge0(
      const RegisterType &ReadRRegisterFieldsRegister,
      const RegisterValueType ReadRRegisterFieldsRegisterValue)
      : ReadWRegisterFieldsType(ReadRRegisterFieldsRegister,
                                ReadRRegisterFieldsRegisterValue),
        ReadRRegisterFieldsType(ReadRRegisterFieldsRegister,
                                ReadRRegisterFieldsRegisterValue) {}
};

} // namespace detail

namespace detail {

template <class WRegisterFieldsRegisterType,
          bool WRegisterFieldsMightAllFieldsBeWritten,
          typename WRegisterFieldsRegisterType::ValueType
              WRegisterFieldsRegisterResetValue,
          class WRegisterFieldsFieldType,
          class... WRegisterFieldsFieldTypesgep1Types>
class WRegisterFields;
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
class WRegisterFields<
    WRegisterFieldsRegisterType, WRegisterFieldsMightAllFieldsBeWritten,
    WRegisterFieldsRegisterResetValue, WRegisterFieldsFieldType> {
protected:
  const WRegisterFieldsRegisterType &R;

public:
  explicit WRegisterFields(
      const WRegisterFieldsRegisterType &WRegisterFieldsRegister)
      : R(WRegisterFieldsRegister) {}

private:
  using WRegisterFieldsType = WRegisterFields<
      WRegisterFieldsRegisterType, WRegisterFieldsMightAllFieldsBeWritten,
      WRegisterFieldsRegisterResetValue, WRegisterFieldsFieldType>;
  using WriteField0Type =
      WriteField0<WRegisterFieldsRegisterType,
                  WRegisterFieldsMightAllFieldsBeWritten,
                  WRegisterFieldsRegisterResetValue, WRegisterFieldsType,
                  WRegisterFieldsFieldType>;

public:
  auto write(const WRegisterFieldsFieldType F) const {
    return WriteField0Type(this->R, F);
  }
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
  using WRegisterFieldsgep1Type =
      WRegisterFields<WRegisterFieldsRegisterType, false,
                      WRegisterFieldsRegisterResetValue,
                      WRegisterFieldsFieldTypesgep1Types...>;

public:
  using WRegisterFieldsgep1Type::write;

  explicit WRegisterFields(
      const WRegisterFieldsRegisterType &WRegisterFieldsRegister)
      : WRegisterFieldsgep1Type(WRegisterFieldsRegister) {}

private:
  using WRegisterFieldsType = WRegisterFields<
      WRegisterFieldsRegisterType, WRegisterFieldsMightAllFieldsBeWritten,
      WRegisterFieldsRegisterResetValue, WRegisterFieldsFieldType,
      WRegisterFieldsFieldTypesgep1Types...>;
  using WriteField0WRegisterFieldsType = WriteField0WRegisterFields<
      WRegisterFieldsRegisterType, WRegisterFieldsMightAllFieldsBeWritten,
      WRegisterFieldsRegisterResetValue, WRegisterFieldsType,
      WRegisterFieldsFieldType, WRegisterFieldsFieldTypesgep1Types...>;

public:
  auto write(const WRegisterFieldsFieldType F) const {
    return WriteField0WRegisterFieldsType(this->R, F);
  }
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteType>
class Write {
protected:
  const WriteRegisterType &R;

public:
  Write(const WriteRegisterType &WriteRegister) : R(WriteRegister) {}

private:
  using RegisterValueType = typename WriteRegisterType::ValueType;

public:
  void write() const {
    RegisterValueType RegisterValue;

    if constexpr (!WriteMightAllFieldsBeWritten)
      RegisterValue = this->R.read();
    else
      RegisterValue = WriteRegisterResetValue;

    this->R.write((RegisterValue & WriteWriteType::getInverseMask()) |
                  *static_cast<const WriteWriteType *>(this));
  }
};

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
  using WriteField0Type =
      WriteField0<WriteRegisterType, WriteMightAllFieldsBeWritten,
                  WriteRegisterResetValue, WriteWRegisterFieldsm1Type,
                  WriteWRegisterFieldsm1FieldType>;
  using WriteType = Write<WriteRegisterType, WriteMightAllFieldsBeWritten,
                          WriteRegisterResetValue, WriteField0Type>;
  friend WriteType;
  static constexpr auto InverseMask{
      ~(WriteWRegisterFieldsm1FieldType::getMask())};
  using RegisterValueType = typename WriteRegisterType::ValueType;
  const RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  operator RegisterValueType() const { return this->V; }

public:
  explicit WriteField0(
      const WriteRegisterType &WriteRegister,
      const WriteWRegisterFieldsm1FieldType WriteWRegisterFieldsm1Field)
      : WriteType(WriteRegister), V(WriteWRegisterFieldsm1Field) {}
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
  using WriteField0WRegisterFieldsType = WriteField0WRegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteWRegisterFieldsm1Type, WriteWRegisterFieldsm1FieldType,
      WriteFieldType>;
  template <bool MAFBW>
  using WriteFieldsle1Type =
      WriteFieldslege1<WriteRegisterType, MAFBW, WriteRegisterResetValue,
                       WriteField0WRegisterFieldsType, WriteFieldType>;
  friend WriteFieldsle1Type<WriteMightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0Type =
      WriteField0<WriteRegisterType, false, WriteRegisterResetValue,
                  WriteWRegisterFieldsm1Type, WriteWRegisterFieldsm1FieldType>;

protected:
  using WriteField0Type::getInverseMask;

private:
  using RegisterValueType = typename WriteRegisterType::ValueType;

protected:
  using WriteField0Type::operator RegisterValueType;

public:
  using WriteField0Type::write;

  explicit WriteField0WRegisterFields(
      const WriteRegisterType &WriteRegister,
      const WriteWRegisterFieldsm1FieldType WriteWRegisterFieldsm1Field)
      : WriteField0Type(WriteRegister, WriteWRegisterFieldsm1Field) {}

  auto write(const WriteFieldType F) const {
    return WriteFieldsle1Type<WriteMightAllFieldsBeWritten>(this->R, *this, F);
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
  using WriteField0WRegisterFieldsType = WriteField0WRegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteWRegisterFieldsm1Type, WriteWRegisterFieldsm1FieldType,
      WriteFieldType, WriteFieldsgep1Types...>;
  template <bool MAFBW>
  using WriteFieldsle1Type =
      WriteFieldslege1<WriteRegisterType, MAFBW, WriteRegisterResetValue,
                       WriteField0WRegisterFieldsType, WriteFieldType>;
  friend WriteFieldsle1Type<WriteMightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0WRegisterFieldsgep1Type = WriteField0WRegisterFields<
      WriteRegisterType, false, WriteRegisterResetValue,
      WriteWRegisterFieldsm1Type, WriteWRegisterFieldsm1FieldType,
      WriteFieldsgep1Types...>;

protected:
  using WriteField0WRegisterFieldsgep1Type::getInverseMask;

private:
  using RegisterValueType = typename WriteRegisterType::ValueType;

protected:
  using WriteField0WRegisterFieldsgep1Type::operator RegisterValueType;

public:
  using WriteField0WRegisterFieldsgep1Type::write;

  explicit WriteField0WRegisterFields(
      const WriteRegisterType &WriteRegister,
      const WriteWRegisterFieldsm1FieldType WriteWRegisterFieldsm1Field)
      : WriteField0WRegisterFieldsgep1Type(WriteRegister,
                                           WriteWRegisterFieldsm1Field) {}

private:
  using WriteFieldsle1WRegisterFieldsType = WriteFieldslege1WRegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteField0WRegisterFieldsType, WriteFieldType, WriteFieldsgep1Types...>;

public:
  auto write(const WriteFieldType F) const {
    return WriteFieldsle1WRegisterFieldsType(this->R, *this, F);
  }
};

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
  using WriteFieldslege1Type =
      WriteFieldslege1<WriteRegisterType, WriteMightAllFieldsBeWritten,
                       WriteRegisterResetValue,
                       WriteWriteFieldslem1WRegisterFieldsType,
                       WriteWriteFieldslem1WRegisterFieldsFieldType>;
  using WriteType = Write<WriteRegisterType, WriteMightAllFieldsBeWritten,
                          WriteRegisterResetValue, WriteFieldslege1Type>;
  friend WriteType;
  static constexpr auto InverseMask{
      ~(WriteWriteFieldslem1WRegisterFieldsFieldType::getMask()) &
      WriteWriteFieldslem1WRegisterFieldsType::getInverseMask()};

protected:
  const WriteWriteFieldslem1WRegisterFieldsType
      &WriteFieldslem1WRegisterFields;

private:
  using RegisterValueType = typename WriteRegisterType::ValueType;
  RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  operator RegisterValueType() const { return this->V; }

public:
  explicit WriteFieldslege1(const WriteRegisterType &WriteRegister,
                            const WriteWriteFieldslem1WRegisterFieldsType
                                &WriteWriteFieldslem1WRegisterFields,
                            const WriteWriteFieldslem1WRegisterFieldsFieldType
                                WriteWriteFieldslem1WRegisterFieldsField)
      : WriteType(WriteRegister),
        WriteFieldslem1WRegisterFields(WriteWriteFieldslem1WRegisterFields),
        V(WriteWriteFieldslem1WRegisterFieldsField |
          WriteWriteFieldslem1WRegisterFields) {}
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
  using WriteFieldslege1WRegisterFieldsType = WriteFieldslege1WRegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteWriteFieldslem1WRegisterFieldsType,
      WriteWriteFieldslem1WRegisterFieldsFieldType, WriteFieldType>;
  template <bool MAFBW>
  using WriteFieldslep1Type =
      WriteFieldslege1<WriteRegisterType, MAFBW, WriteRegisterResetValue,
                       WriteFieldslege1WRegisterFieldsType, WriteFieldType>;
  friend WriteFieldslep1Type<WriteMightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1Type =
      WriteFieldslege1<WriteRegisterType, false, WriteRegisterResetValue,
                       WriteWriteFieldslem1WRegisterFieldsType,
                       WriteWriteFieldslem1WRegisterFieldsFieldType>;

protected:
  using WriteFieldslege1Type::getInverseMask;

private:
  using RegisterValueType = typename WriteRegisterType::ValueType;

protected:
  using WriteFieldslege1Type::operator RegisterValueType;

public:
  using WriteFieldslege1Type::write;

  explicit WriteFieldslege1WRegisterFields(
      const WriteRegisterType &WriteRegister,
      const WriteWriteFieldslem1WRegisterFieldsType
          &WriteWriteFieldslem1WRegisterFields,
      const WriteWriteFieldslem1WRegisterFieldsFieldType
          WriteWriteFieldslem1WRegisterFieldsField)
      : WriteFieldslege1Type(WriteRegister,
                             WriteWriteFieldslem1WRegisterFields,
                             WriteWriteFieldslem1WRegisterFieldsField) {}

  auto write(const WriteFieldType F) const {
    return WriteFieldslep1Type<WriteMightAllFieldsBeWritten>(this->R, *this,
                                                             F);
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
  using WriteFieldslege1WRegisterFieldsType = WriteFieldslege1WRegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteWriteFieldslem1WRegisterFieldsType,
      WriteWriteFieldslem1WRegisterFieldsFieldType, WriteFieldType,
      WriteFieldsgep1Types...>;
  template <bool MAFBW>
  using WriteFieldslep1Type =
      WriteFieldslege1<WriteRegisterType, MAFBW, WriteRegisterResetValue,
                       WriteFieldslege1WRegisterFieldsType, WriteFieldType>;
  friend WriteFieldslep1Type<WriteMightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1WRegisterFieldsgep1Type =
      WriteFieldslege1WRegisterFields<
          WriteRegisterType, false, WriteRegisterResetValue,
          WriteWriteFieldslem1WRegisterFieldsType,
          WriteWriteFieldslem1WRegisterFieldsFieldType,
          WriteFieldsgep1Types...>;

protected:
  using WriteFieldslege1WRegisterFieldsgep1Type::getInverseMask;

private:
  using RegisterValueType = typename WriteRegisterType::ValueType;

protected:
  using WriteFieldslege1WRegisterFieldsgep1Type::operator RegisterValueType;

public:
  using WriteFieldslege1WRegisterFieldsgep1Type::write;

  explicit WriteFieldslege1WRegisterFields(
      const WriteRegisterType &WriteRegister,
      const WriteWriteFieldslem1WRegisterFieldsType
          &WriteWriteFieldslem1WRegisterFields,
      const WriteWriteFieldslem1WRegisterFieldsFieldType
          WriteWriteFieldslem1WRegisterFieldsField)
      : WriteFieldslege1WRegisterFieldsgep1Type(
            WriteRegister, WriteWriteFieldslem1WRegisterFields,
            WriteWriteFieldslem1WRegisterFieldsField) {}

private:
  using WriteFieldslep1WRegisterFieldsType = WriteFieldslege1WRegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteFieldslege1WRegisterFieldsType, WriteFieldType,
      WriteFieldsgep1Types...>;

public:
  auto write(const WriteFieldType F) const {
    return WriteFieldslep1WRegisterFieldsType(this->R, *this, F);
  }
};

} // namespace detail

namespace detail {

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
class ReadWRegisterFields<ReadWRegisterFieldsRegisterType,
                          ReadWRegisterFieldsFieldType> {
protected:
  const ReadWRegisterFieldsRegisterType &R;

private:
  using RegisterValueType =
      typename ReadWRegisterFieldsRegisterType::ValueType;

protected:
  const RegisterValueType RegisterValue;

public:
  explicit ReadWRegisterFields(
      const ReadWRegisterFieldsRegisterType &ReadWRegisterFieldsRegister,
      const RegisterValueType ReadWRegisterFieldsRegisterValue)
      : R(ReadWRegisterFieldsRegister),
        RegisterValue(ReadWRegisterFieldsRegisterValue) {}

private:
  using ReadWRegisterFieldsType =
      ReadWRegisterFields<ReadWRegisterFieldsRegisterType,
                          ReadWRegisterFieldsFieldType>;
  using ReadWriteField0Type =
      ReadWriteField0<ReadWRegisterFieldsRegisterType, ReadWRegisterFieldsType,
                      ReadWRegisterFieldsFieldType>;

public:
  auto write(const ReadWRegisterFieldsFieldType F) const {
    return ReadWriteField0Type(this->R, this->RegisterValue, F);
  }
};

template <class ReadWRegisterFieldsRegisterType,
          class ReadWRegisterFieldsFieldType,
          class... ReadWRegisterFieldsFieldTypesgep1Types>
class ReadWRegisterFields
    : public ReadWRegisterFields<ReadWRegisterFieldsRegisterType,
                                 ReadWRegisterFieldsFieldTypesgep1Types...> {
  using ReadWRegisterFieldsgep1Type =
      ReadWRegisterFields<ReadWRegisterFieldsRegisterType,
                          ReadWRegisterFieldsFieldTypesgep1Types...>;

public:
  using ReadWRegisterFieldsgep1Type::write;

private:
  using RegisterValueType =
      typename ReadWRegisterFieldsRegisterType::ValueType;

public:
  explicit ReadWRegisterFields(
      const ReadWRegisterFieldsRegisterType &ReadWRegisterFieldsRegister,
      const RegisterValueType ReadWRegisterFieldsRegisterValue)
      : ReadWRegisterFieldsgep1Type(ReadWRegisterFieldsRegister,
                                    ReadWRegisterFieldsRegisterValue) {}

private:
  using ReadWRegisterFieldsType =
      ReadWRegisterFields<ReadWRegisterFieldsRegisterType,
                          ReadWRegisterFieldsFieldType,
                          ReadWRegisterFieldsFieldTypesgep1Types...>;
  using ReadWriteField0WRegisterFieldsType = ReadWriteField0WRegisterFields<
      ReadWRegisterFieldsRegisterType, ReadWRegisterFieldsType,
      ReadWRegisterFieldsFieldType, ReadWRegisterFieldsFieldTypesgep1Types...>;

public:
  auto write(const ReadWRegisterFieldsFieldType F) const {
    return ReadWriteField0WRegisterFieldsType(this->R, this->RegisterValue, F);
  }
};

template <class ReadWriteRegisterType, class ReadWriteReadWriteType>
class ReadWrite {
protected:
  const ReadWriteRegisterType &R;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;

protected:
  const RegisterValueType RegisterValue;

public:
  explicit ReadWrite(const ReadWriteRegisterType &ReadWriteRegister,
                     const RegisterValueType ReadWriteRegisterValue)
      : R(ReadWriteRegister), RegisterValue(ReadWriteRegisterValue) {}

  void write() const {
    this->R.write(
        (this->RegisterValue & ReadWriteReadWriteType::getInverseMask()) |
        *static_cast<const ReadWriteReadWriteType *>(this));
  }
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWRegisterFieldsm1Type,
          class ReadWriteReadWRegisterFieldsm1FieldType>
class ReadWriteField0
    : public ReadWrite<
          ReadWriteRegisterType,
          ReadWriteField0<ReadWriteRegisterType,
                          ReadWriteReadWRegisterFieldsm1Type,
                          ReadWriteReadWRegisterFieldsm1FieldType>> {
  using ReadWriteField0Type =
      ReadWriteField0<ReadWriteRegisterType,
                      ReadWriteReadWRegisterFieldsm1Type,
                      ReadWriteReadWRegisterFieldsm1FieldType>;
  using ReadWriteType = ReadWrite<ReadWriteRegisterType, ReadWriteField0Type>;
  friend ReadWriteType;
  static constexpr auto InverseMask{
      ~(ReadWriteReadWRegisterFieldsm1FieldType::getMask())};
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;
  const RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  operator RegisterValueType() const { return this->V; }

public:
  explicit ReadWriteField0(const ReadWriteRegisterType &ReadWriteRegister,
                           const RegisterValueType ReadWriteRegisterValue,
                           const ReadWriteReadWRegisterFieldsm1FieldType
                               ReadWriteReadWRegisterFieldsm1Field)
      : ReadWriteType(ReadWriteRegister, ReadWriteRegisterValue),
        V(ReadWriteReadWRegisterFieldsm1Field) {}
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
  using ReadWriteField0WRegisterFieldsType = ReadWriteField0WRegisterFields<
      ReadWriteRegisterType, ReadWriteReadWRegisterFieldsm1Type,
      ReadWriteReadWRegisterFieldsm1FieldType, ReadWriteFieldType>;
  using ReadWriteFieldsle1Type =
      ReadWriteFieldslege1<ReadWriteRegisterType,
                           ReadWriteField0WRegisterFieldsType,
                           ReadWriteFieldType>;
  friend ReadWriteFieldsle1Type;
  using ReadWriteField0Type =
      ReadWriteField0<ReadWriteRegisterType,
                      ReadWriteReadWRegisterFieldsm1Type,
                      ReadWriteReadWRegisterFieldsm1FieldType>;

protected:
  using ReadWriteField0Type::getInverseMask;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;

protected:
  using ReadWriteField0Type::operator RegisterValueType;

public:
  using ReadWriteField0Type::write;

  explicit ReadWriteField0WRegisterFields(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWRegisterFieldsm1FieldType
          ReadWriteReadWRegisterFieldsm1Field)
      : ReadWriteField0Type(ReadWriteRegister, ReadWriteRegisterValue,
                            ReadWriteReadWRegisterFieldsm1Field) {}

  auto write(const ReadWriteFieldType F) const {
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
  using ReadWriteField0WRegisterFieldsType = ReadWriteField0WRegisterFields<
      ReadWriteRegisterType, ReadWriteReadWRegisterFieldsm1Type,
      ReadWriteReadWRegisterFieldsm1FieldType, ReadWriteFieldType,
      ReadWriteFieldsgep1Types...>;
  friend ReadWriteFieldslege1<ReadWriteRegisterType,
                              ReadWriteField0WRegisterFieldsType,
                              ReadWriteFieldType>;
  using ReadWriteField0WRegisterFieldsgep1Type =
      ReadWriteField0WRegisterFields<ReadWriteRegisterType,
                                     ReadWriteReadWRegisterFieldsm1Type,
                                     ReadWriteReadWRegisterFieldsm1FieldType,
                                     ReadWriteFieldsgep1Types...>;

protected:
  using ReadWriteField0WRegisterFieldsgep1Type::getInverseMask;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;

protected:
  using ReadWriteField0WRegisterFieldsgep1Type::operator RegisterValueType;

public:
  using ReadWriteField0WRegisterFieldsgep1Type::write;

  explicit ReadWriteField0WRegisterFields(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWRegisterFieldsm1FieldType
          ReadWriteReadWRegisterFieldsm1Field)
      : ReadWriteField0WRegisterFieldsgep1Type(
            ReadWriteRegister, ReadWriteRegisterValue,
            ReadWriteReadWRegisterFieldsm1Field) {}

private:
  using ReadWriteFieldsle1WRegisterFieldsType =
      ReadWriteFieldslege1WRegisterFields<
          ReadWriteRegisterType, ReadWriteField0WRegisterFieldsType,
          ReadWriteFieldType, ReadWriteFieldsgep1Types...>;

public:
  auto write(const ReadWriteFieldType F) const {
    return ReadWriteFieldsle1WRegisterFieldsType(this->R, this->RegisterValue,
                                                 *this, F);
  }
};

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
  using ReadWriteFieldslege1Type = ReadWriteFieldslege1<
      ReadWriteRegisterType, ReadWriteReadWriteFieldslem1WRegisterFieldsType,
      ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType>;
  using ReadWriteType =
      ReadWrite<ReadWriteRegisterType, ReadWriteFieldslege1Type>;
  friend ReadWriteType;
  static constexpr auto InverseMask{
      ~(ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType::getMask()) &
      ReadWriteReadWriteFieldslem1WRegisterFieldsType::getInverseMask()};

protected:
  const ReadWriteReadWriteFieldslem1WRegisterFieldsType
      &ReadWriteFieldslem1WRegisterFields;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;
  const RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  operator RegisterValueType() const { return this->V; }

public:
  explicit ReadWriteFieldslege1(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWriteFieldslem1WRegisterFieldsType
          &ReadWriteReadWriteFieldslem1WRegisterFields,
      const ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType
          ReadWriteReadWriteFieldslem1WRegisterFieldsField)
      : ReadWriteType(ReadWriteRegister, ReadWriteRegisterValue),
        ReadWriteFieldslem1WRegisterFields(
            ReadWriteReadWriteFieldslem1WRegisterFields),
        V(ReadWriteReadWriteFieldslem1WRegisterFieldsField |
          ReadWriteReadWriteFieldslem1WRegisterFields) {}
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
  using ReadWriteFieldslege1WRegisterFieldsType =
      ReadWriteFieldslege1WRegisterFields<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType,
          ReadWriteFieldType>;
  using ReadWriteFieldslep1Type =
      ReadWriteFieldslege1<ReadWriteRegisterType,
                           ReadWriteFieldslege1WRegisterFieldsType,
                           ReadWriteFieldType>;
  friend ReadWriteFieldslep1Type;
  using ReadWriteFieldslege1Type = ReadWriteFieldslege1<
      ReadWriteRegisterType, ReadWriteReadWriteFieldslem1WRegisterFieldsType,
      ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType>;

protected:
  using ReadWriteFieldslege1Type::getInverseMask;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;

protected:
  using ReadWriteFieldslege1Type::operator RegisterValueType;

public:
  using ReadWriteFieldslege1Type::write;

  explicit ReadWriteFieldslege1WRegisterFields(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWriteFieldslem1WRegisterFieldsType
          &ReadWriteReadWriteFieldslem1WRegisterFields,
      const ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType
          ReadWriteReadWriteFieldslem1WRegisterFieldsField)
      : ReadWriteFieldslege1Type(
            ReadWriteRegister, ReadWriteRegisterValue,
            ReadWriteReadWriteFieldslem1WRegisterFields,
            ReadWriteReadWriteFieldslem1WRegisterFieldsField) {}

  auto write(const ReadWriteFieldType F) const {
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
  using ReadWriteFieldslege1WRegisterFieldsType =
      ReadWriteFieldslege1WRegisterFields<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType,
          ReadWriteFieldType, ReadWriteFieldsgep1Types...>;
  friend ReadWriteFieldslege1<ReadWriteRegisterType,
                              ReadWriteFieldslege1WRegisterFieldsType,
                              ReadWriteFieldType>;
  using ReadWriteFieldslege1WRegisterFieldsgep1Type =
      ReadWriteFieldslege1WRegisterFields<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsType,
          ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType,
          ReadWriteFieldsgep1Types...>;

protected:
  using ReadWriteFieldslege1WRegisterFieldsgep1Type::getInverseMask;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;

protected:
  using ReadWriteFieldslege1WRegisterFieldsgep1Type::
  operator RegisterValueType;

public:
  using ReadWriteFieldslege1WRegisterFieldsgep1Type::write;

  explicit ReadWriteFieldslege1WRegisterFields(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWriteFieldslem1WRegisterFieldsType
          &ReadWriteReadWriteFieldslem1WRegisterFields,
      const ReadWriteReadWriteFieldslem1WRegisterFieldsFieldType
          ReadWriteReadWriteFieldslem1WRegisterFieldsField)
      : ReadWriteFieldslege1WRegisterFieldsgep1Type(
            ReadWriteRegister, ReadWriteRegisterValue,
            ReadWriteReadWriteFieldslem1WRegisterFields,
            ReadWriteReadWriteFieldslem1WRegisterFieldsField) {}

private:
  using ReadWriteFieldslep1WRegisterFieldsType =
      ReadWriteFieldslege1WRegisterFields<
          ReadWriteRegisterType, ReadWriteFieldslege1WRegisterFieldsType,
          ReadWriteFieldType, ReadWriteFieldsgep1Types...>;

public:
  auto write(const ReadWriteFieldType F) const {
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
