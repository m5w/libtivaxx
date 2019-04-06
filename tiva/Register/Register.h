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

namespace tiva {

namespace {

template <class WriteRegisterFieldsRegisterType,
          bool WriteRegisterFieldsMightAllFieldsBeWritten,
          typename WriteRegisterFieldsRegisterType::ValueType
              WriteRegisterFieldsRegisterResetValue,
          class WriteRegisterFieldsFieldType,
          class... WriteRegisterFieldsFieldTypesgep1Types>
class WriteRegisterFields;
template <class ReadWriteRegisterFieldsRegisterType,
          class ReadWriteRegisterFieldsFieldType,
          class... ReadWriteRegisterFieldsFieldTypesgep1Types>
class ReadWriteRegisterFields;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteType>
class Write;
template <class ReadWriteRegisterType, class ReadWriteReadWriteType>
class ReadWrite;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteRegisterFieldsm1Type,
          class WriteWriteRegisterFieldsm1FieldType>
class WriteField0;
template <class ReadWriteRegisterType,
          class ReadWriteReadWriteRegisterFieldsm1Type,
          class ReadWriteReadWriteRegisterFieldsm1FieldType>
class ReadWriteField0;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteRegisterFieldsm1Type,
          class WriteWriteRegisterFieldsm1FieldType, class WriteFieldType,
          class... WriteFieldsgep1Types>
class WriteField0RegisterFields;
template <class ReadWriteRegisterType,
          class ReadWriteReadWriteRegisterFieldsm1Type,
          class ReadWriteReadWriteRegisterFieldsm1FieldType,
          class ReadWriteFieldType, class... ReadWriteFieldsgep1Types>
class ReadWriteField0RegisterFields;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1RegisterFieldsType,
          class WriteWriteFieldslem1RegisterFieldsFieldType>
class WriteFieldslege1;
template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsFieldType>
class ReadWriteFieldslege1;
template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1RegisterFieldsType,
          class WriteWriteFieldslem1RegisterFieldsFieldType,
          class WriteFieldType, class... WriteFieldsgep1Types>
class WriteFieldslege1RegisterFields;
template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsFieldType,
          class ReadWriteFieldType, class... ReadWriteFieldsgep1Types>
class ReadWriteFieldslege1RegisterFields;

template <class WriteRegisterFieldsRegisterType,
          bool WriteRegisterFieldsMightAllFieldsBeWritten,
          typename WriteRegisterFieldsRegisterType::ValueType
              WriteRegisterFieldsRegisterResetValue,
          class WriteRegisterFieldsFieldType>
class WriteRegisterFields<WriteRegisterFieldsRegisterType,
                          WriteRegisterFieldsMightAllFieldsBeWritten,
                          WriteRegisterFieldsRegisterResetValue,
                          WriteRegisterFieldsFieldType> {
protected:
  const WriteRegisterFieldsRegisterType &R;

public:
  WriteRegisterFields(
      const WriteRegisterFieldsRegisterType &WriteRegisterFieldsRegister)
      : R(WriteRegisterFieldsRegister) {}

private:
  using WriteRegisterFieldsType =
      WriteRegisterFields<WriteRegisterFieldsRegisterType,
                          WriteRegisterFieldsMightAllFieldsBeWritten,
                          WriteRegisterFieldsRegisterResetValue,
                          WriteRegisterFieldsFieldType>;
  using WriteField0Type =
      WriteField0<WriteRegisterFieldsRegisterType,
                  WriteRegisterFieldsMightAllFieldsBeWritten,
                  WriteRegisterFieldsRegisterResetValue,
                  WriteRegisterFieldsType, WriteRegisterFieldsFieldType>;

public:
  auto write(const WriteRegisterFieldsFieldType F) const {
    return WriteField0Type(this->R, F);
  }
};

template <class ReadWriteRegisterFieldsRegisterType,
          class ReadWriteRegisterFieldsFieldType>
class ReadWriteRegisterFields<ReadWriteRegisterFieldsRegisterType,
                              ReadWriteRegisterFieldsFieldType> {
protected:
  const ReadWriteRegisterFieldsRegisterType &R;

private:
  using RegisterValueType =
      typename ReadWriteRegisterFieldsRegisterType::ValueType;

protected:
  const RegisterValueType RegisterValue;

public:
  ReadWriteRegisterFields(
      const ReadWriteRegisterFieldsRegisterType
          &ReadWriteRegisterFieldsRegister,
      const RegisterValueType ReadWriteRegisterFieldsRegisterValue)
      : R(ReadWriteRegisterFieldsRegister),
        RegisterValue(ReadWriteRegisterFieldsRegisterValue) {}

private:
  using ReadWriteRegisterFieldsType =
      ReadWriteRegisterFields<ReadWriteRegisterFieldsRegisterType,
                              ReadWriteRegisterFieldsFieldType>;
  using ReadWriteField0Type =
      ReadWriteField0<ReadWriteRegisterFieldsRegisterType,
                      ReadWriteRegisterFieldsType,
                      ReadWriteRegisterFieldsFieldType>;

public:
  auto write(const ReadWriteRegisterFieldsFieldType F) const {
    return ReadWriteField0Type(this->R, this->RegisterValue, F);
  }
};

template <class WriteRegisterFieldsRegisterType,
          bool WriteRegisterFieldsMightAllFieldsBeWritten,
          typename WriteRegisterFieldsRegisterType::ValueType
              WriteRegisterFieldsRegisterResetValue,
          class WriteRegisterFieldsFieldType,
          class... WriteRegisterFieldsFieldTypesgep1Types>
class WriteRegisterFields
    : public WriteRegisterFields<WriteRegisterFieldsRegisterType, false,
                                 WriteRegisterFieldsRegisterResetValue,
                                 WriteRegisterFieldsFieldTypesgep1Types...> {
  using WriteRegisterFieldsgep1Type =
      WriteRegisterFields<WriteRegisterFieldsRegisterType, false,
                          WriteRegisterFieldsRegisterResetValue,
                          WriteRegisterFieldsFieldTypesgep1Types...>;

public:
  using WriteRegisterFieldsgep1Type::write;

  WriteRegisterFields(
      const WriteRegisterFieldsRegisterType &WriteRegisterFieldsRegister)
      : WriteRegisterFieldsgep1Type(WriteRegisterFieldsRegister) {}

private:
  using WriteRegisterFieldsType =
      WriteRegisterFields<WriteRegisterFieldsRegisterType,
                          WriteRegisterFieldsMightAllFieldsBeWritten,
                          WriteRegisterFieldsRegisterResetValue,
                          WriteRegisterFieldsFieldType,
                          WriteRegisterFieldsFieldTypesgep1Types...>;
  using WriteField0RegisterFieldsType = WriteField0RegisterFields<
      WriteRegisterFieldsRegisterType,
      WriteRegisterFieldsMightAllFieldsBeWritten,
      WriteRegisterFieldsRegisterResetValue, WriteRegisterFieldsType,
      WriteRegisterFieldsFieldType, WriteRegisterFieldsFieldTypesgep1Types...>;

public:
  auto write(const WriteRegisterFieldsFieldType F) const {
    return WriteField0RegisterFieldsType(this->R, F);
  }
};

template <class ReadWriteRegisterFieldsRegisterType,
          class ReadWriteRegisterFieldsFieldType,
          class... ReadWriteRegisterFieldsFieldTypesgep1Types>
class ReadWriteRegisterFields
    : public ReadWriteRegisterFields<
          ReadWriteRegisterFieldsRegisterType,
          ReadWriteRegisterFieldsFieldTypesgep1Types...> {
  using ReadWriteRegisterFieldsgep1Type =
      ReadWriteRegisterFields<ReadWriteRegisterFieldsRegisterType,
                              ReadWriteRegisterFieldsFieldTypesgep1Types...>;

public:
  using ReadWriteRegisterFieldsgep1Type::write;

private:
  using RegisterValueType =
      typename ReadWriteRegisterFieldsRegisterType::ValueType;

  ReadWriteRegisterFields(
      const ReadWriteRegisterFieldsRegisterType
          &ReadWriteRegisterFieldsRegister,
      const RegisterValueType ReadWriteRegisterFieldsRegisterValue)
      : ReadWriteRegisterFieldsgep1Type(ReadWriteRegisterFieldsRegister,
                                        ReadWriteRegisterFieldsRegisterValue) {
  }

private:
  using ReadWriteRegisterFieldsType =
      ReadWriteRegisterFields<ReadWriteRegisterFieldsRegisterType,
                              ReadWriteRegisterFieldsFieldType,
                              ReadWriteRegisterFieldsFieldTypesgep1Types...>;
  using ReadWriteField0RegisterFieldsType = ReadWriteField0RegisterFields<
      ReadWriteRegisterFieldsRegisterType, ReadWriteRegisterFieldsType,
      ReadWriteRegisterFieldsFieldType,
      ReadWriteRegisterFieldsFieldTypesgep1Types...>;

public:
  auto write(const ReadWriteRegisterFieldsFieldType F) const {
    return ReadWriteField0RegisterFieldsType(this->R, this->RegisterValue, F);
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
                  static_cast<const WriteWriteType *>(this)->getValue());
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
  ReadWrite(const ReadWriteRegisterType &ReadWriteRegister,
            const RegisterValueType ReadWriteRegisterValue)
      : R(ReadWriteRegister), RegisterValue(ReadWriteRegisterValue) {}

  void write() const {
    this->R.write(
        (this->RegisterValue & ReadWriteReadWriteType::getInverseMask()) |
        static_cast<const ReadWriteReadWriteType *>(this)->getValue());
  }
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteRegisterFieldsm1Type,
          class WriteWriteRegisterFieldsm1FieldType>
class WriteField0
    : public Write<
          WriteRegisterType, WriteMightAllFieldsBeWritten,
          WriteRegisterResetValue,
          WriteField0<WriteRegisterType, WriteMightAllFieldsBeWritten,
                      WriteRegisterResetValue, WriteWriteRegisterFieldsm1Type,
                      WriteWriteRegisterFieldsm1FieldType>> {
  using WriteField0Type =
      WriteField0<WriteRegisterType, WriteMightAllFieldsBeWritten,
                  WriteRegisterResetValue, WriteWriteRegisterFieldsm1Type,
                  WriteWriteRegisterFieldsm1FieldType>;
  using WriteType = Write<WriteRegisterType, WriteMightAllFieldsBeWritten,
                          WriteRegisterResetValue, WriteField0Type>;
  friend WriteType;
  static constexpr auto InverseMask{
      ~(WriteWriteRegisterFieldsm1FieldType::getMask())};
  using RegisterValueType = typename WriteRegisterType::ValueType;
  const RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  auto getValue() const { return this->V; }

public:
  WriteField0(const WriteRegisterType &WriteRegister,
              const WriteWriteRegisterFieldsm1FieldType
                  WriteWriteRegisterFieldsm1Field)
      : WriteType(WriteRegister), V(WriteWriteRegisterFieldsm1Field) {}
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteRegisterFieldsm1Type,
          class ReadWriteReadWriteRegisterFieldsm1FieldType>
class ReadWriteField0
    : public ReadWrite<
          ReadWriteRegisterType,
          ReadWriteField0<ReadWriteRegisterType,
                          ReadWriteReadWriteRegisterFieldsm1Type,
                          ReadWriteReadWriteRegisterFieldsm1FieldType>> {
  using ReadWriteField0Type =
      ReadWriteField0<ReadWriteRegisterType,
                      ReadWriteReadWriteRegisterFieldsm1Type,
                      ReadWriteReadWriteRegisterFieldsm1FieldType>;
  using ReadWriteType = ReadWrite<ReadWriteRegisterType, ReadWriteField0Type>;
  friend ReadWriteType;
  static constexpr auto InverseMask{
      ~(ReadWriteReadWriteRegisterFieldsm1FieldType::getMask())};
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;
  const RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  auto getValue() const { return this->V; }

public:
  ReadWriteField0(const ReadWriteRegisterType &ReadWriteRegister,
                  const RegisterValueType ReadWriteRegisterValue,
                  const ReadWriteReadWriteRegisterFieldsm1FieldType
                      ReadWriteReadWriteRegisterFieldsm1Field)
      : ReadWriteType(ReadWriteRegister, ReadWriteRegisterValue),
        V(ReadWriteReadWriteRegisterFieldsm1Field) {}
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteRegisterFieldsm1Type,
          class WriteWriteRegisterFieldsm1FieldType, class WriteFieldType>
class WriteField0RegisterFields<
    WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
    WriteWriteRegisterFieldsm1Type, WriteWriteRegisterFieldsm1FieldType,
    WriteFieldType>
    : public WriteField0<WriteRegisterType, false, WriteRegisterResetValue,
                         WriteWriteRegisterFieldsm1Type,
                         WriteWriteRegisterFieldsm1FieldType> {
  using WriteField0RegisterFieldsType = WriteField0RegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteWriteRegisterFieldsm1Type, WriteWriteRegisterFieldsm1FieldType,
      WriteFieldType>;
  template <bool MightAllFieldsBeWritten>
  using WriteFieldsle1Type =
      WriteFieldslege1<WriteRegisterType, MightAllFieldsBeWritten,
                       WriteRegisterResetValue, WriteField0RegisterFieldsType,
                       WriteFieldType>;
  friend WriteFieldsle1Type<WriteMightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0Type =
      WriteField0<WriteRegisterType, false, WriteRegisterResetValue,
                  WriteWriteRegisterFieldsm1Type,
                  WriteWriteRegisterFieldsm1FieldType>;

protected:
  using WriteField0Type::getInverseMask;
  using WriteField0Type::getValue;

public:
  using WriteField0Type::write;

  WriteField0RegisterFields(const WriteRegisterType &WriteRegister,
                            const WriteWriteRegisterFieldsm1FieldType
                                WriteWriteRegisterFieldsm1Field)
      : WriteField0Type(WriteRegister, WriteWriteRegisterFieldsm1Field) {}

  auto write(const WriteFieldType F) const {
    return WriteFieldsle1Type<WriteMightAllFieldsBeWritten>(this->R, *this, F);
  }
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteRegisterFieldsm1Type,
          class ReadWriteReadWriteRegisterFieldsm1FieldType,
          class ReadWriteFieldType>
class ReadWriteField0RegisterFields<
    ReadWriteRegisterType, ReadWriteReadWriteRegisterFieldsm1Type,
    ReadWriteReadWriteRegisterFieldsm1FieldType, ReadWriteFieldType>
    : public ReadWriteField0<ReadWriteRegisterType,
                             ReadWriteReadWriteRegisterFieldsm1Type,
                             ReadWriteReadWriteRegisterFieldsm1FieldType> {
  using ReadWriteField0RegisterFieldsType = ReadWriteField0RegisterFields<
      ReadWriteRegisterType, ReadWriteReadWriteRegisterFieldsm1Type,
      ReadWriteReadWriteRegisterFieldsm1FieldType, ReadWriteFieldType>;
  using ReadWriteFieldsle1Type =
      ReadWriteFieldslege1<ReadWriteRegisterType,
                           ReadWriteField0RegisterFieldsType,
                           ReadWriteFieldType>;
  friend ReadWriteFieldsle1Type;
  using ReadWriteField0Type =
      ReadWriteField0<ReadWriteRegisterType,
                      ReadWriteReadWriteRegisterFieldsm1Type,
                      ReadWriteReadWriteRegisterFieldsm1FieldType>;

protected:
  using ReadWriteField0Type::getInverseMask;
  using ReadWriteField0Type::getValue;

public:
  using ReadWriteField0Type::write;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;

public:
  ReadWriteField0RegisterFields(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWriteRegisterFieldsm1FieldType
          ReadWriteReadWriteRegisterFieldsm1Field)
      : ReadWriteField0Type(ReadWriteRegister, ReadWriteRegisterValue,
                            ReadWriteReadWriteRegisterFieldsm1Field) {}

  auto write(const ReadWriteFieldType F) const {
    return ReadWriteFieldsle1Type(this->R, this->RegisterValue, *this, F);
  }
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteRegisterFieldsm1Type,
          class WriteWriteRegisterFieldsm1FieldType, class WriteFieldType,
          class... WriteFieldsgep1Types>
class WriteField0RegisterFields
    : public WriteField0RegisterFields<
          WriteRegisterType, false, WriteRegisterResetValue,
          WriteWriteRegisterFieldsm1Type, WriteWriteRegisterFieldsm1FieldType,
          WriteFieldsgep1Types...> {
  using WriteField0RegisterFieldsType = WriteField0RegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteWriteRegisterFieldsm1Type, WriteWriteRegisterFieldsm1FieldType,
      WriteFieldType, WriteFieldsgep1Types...>;
  template <bool MightAllFieldsBeWritten>
  using WriteFieldsle1Type =
      WriteFieldslege1<WriteRegisterType, MightAllFieldsBeWritten,
                       WriteRegisterResetValue, WriteField0RegisterFieldsType,
                       WriteFieldType>;
  friend WriteFieldsle1Type<WriteMightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0RegisterFieldsgep1Type = WriteField0RegisterFields<
      WriteRegisterType, false, WriteRegisterResetValue,
      WriteWriteRegisterFieldsm1Type, WriteWriteRegisterFieldsm1FieldType,
      WriteFieldsgep1Types...>;

protected:
  using WriteField0RegisterFieldsgep1Type::getInverseMask;
  using WriteField0RegisterFieldsgep1Type::getValue;

public:
  using WriteField0RegisterFieldsgep1Type::write;

  WriteField0RegisterFields(const WriteRegisterType &WriteRegister,
                            const WriteWriteRegisterFieldsm1FieldType
                                WriteWriteRegisterFieldsm1Field)
      : WriteField0RegisterFieldsgep1Type(WriteRegister,
                                          WriteWriteRegisterFieldsm1Field) {}

private:
  using WriteFieldsle1RegisterFieldsType = WriteFieldslege1RegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteField0RegisterFieldsType, WriteFieldType, WriteFieldsgep1Types...>;

public:
  auto write(const WriteFieldType F) const {
    return WriteFieldsle1RegisterFieldsType(this->R, *this, F);
  }
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteRegisterFieldsm1Type,
          class ReadWriteReadWriteRegisterFieldsm1FieldType,
          class ReadWriteFieldType, class... ReadWriteFieldsgep1Types>
class ReadWriteField0RegisterFields
    : public ReadWriteField0RegisterFields<
          ReadWriteRegisterType, ReadWriteReadWriteRegisterFieldsm1Type,
          ReadWriteReadWriteRegisterFieldsm1FieldType,
          ReadWriteFieldsgep1Types...> {
  using ReadWriteField0RegisterFieldsType = ReadWriteField0RegisterFields<
      ReadWriteRegisterType, ReadWriteReadWriteRegisterFieldsm1Type,
      ReadWriteReadWriteRegisterFieldsm1FieldType, ReadWriteFieldType,
      ReadWriteFieldsgep1Types...>;
  friend ReadWriteFieldslege1<ReadWriteRegisterType,
                              ReadWriteField0RegisterFieldsType,
                              ReadWriteFieldType>;
  using ReadWriteField0RegisterFieldsgep1Type = ReadWriteField0RegisterFields<
      ReadWriteRegisterType, ReadWriteReadWriteRegisterFieldsm1Type,
      ReadWriteReadWriteRegisterFieldsm1FieldType,
      ReadWriteFieldsgep1Types...>;

protected:
  using ReadWriteField0RegisterFieldsgep1Type::getInverseMask;
  using ReadWriteField0RegisterFieldsgep1Type::getValue;

public:
  using ReadWriteField0RegisterFieldsgep1Type::write;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;

public:
  ReadWriteField0RegisterFields(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWriteRegisterFieldsm1FieldType
          ReadWriteReadWriteRegisterFieldsm1Field)
      : ReadWriteField0RegisterFieldsgep1Type(
            ReadWriteRegister, ReadWriteRegisterValue,
            ReadWriteReadWriteRegisterFieldsm1Field) {}

private:
  using ReadWriteFieldsle1RegisterFieldsType =
      ReadWriteFieldslege1RegisterFields<
          ReadWriteRegisterType, ReadWriteField0RegisterFieldsType,
          ReadWriteFieldType, ReadWriteFieldsgep1Types...>;

public:
  auto write(const ReadWriteFieldType F) const {
    return ReadWriteFieldsle1RegisterFieldsType(this->R, this->RegisterValue,
                                                *this, F);
  }
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1RegisterFieldsType,
          class WriteWriteFieldslem1RegisterFieldsFieldType>
class WriteFieldslege1
    : public Write<
          WriteRegisterType, WriteMightAllFieldsBeWritten,
          WriteRegisterResetValue,
          WriteFieldslege1<WriteRegisterType, WriteMightAllFieldsBeWritten,
                           WriteRegisterResetValue,
                           WriteWriteFieldslem1RegisterFieldsType,
                           WriteWriteFieldslem1RegisterFieldsFieldType>> {
  using WriteFieldslege1Type =
      WriteFieldslege1<WriteRegisterType, WriteMightAllFieldsBeWritten,
                       WriteRegisterResetValue,
                       WriteWriteFieldslem1RegisterFieldsType,
                       WriteWriteFieldslem1RegisterFieldsFieldType>;
  using WriteType = Write<WriteRegisterType, WriteMightAllFieldsBeWritten,
                          WriteRegisterResetValue, WriteFieldslege1Type>;
  friend WriteType;
  static constexpr auto InverseMask{
      ~(WriteWriteFieldslem1RegisterFieldsFieldType::getMask()) &
      WriteWriteFieldslem1RegisterFieldsType::getInverseMask()};

protected:
  const WriteWriteFieldslem1RegisterFieldsType &WriteFieldslem1RegisterFields;

private:
  using RegisterValueType = typename WriteRegisterType::ValueType;
  RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  auto getValue() const { return this->V; }

public:
  WriteFieldslege1(const WriteRegisterType &WriteRegister,
                   const WriteWriteFieldslem1RegisterFieldsType
                       &WriteWriteFieldslem1RegisterFields,
                   const WriteWriteFieldslem1RegisterFieldsFieldType
                       WriteWriteFieldslem1RegisterFieldsField)
      : WriteType(WriteRegister),
        WriteFieldslem1RegisterFields(WriteWriteFieldslem1RegisterFields),
        V(WriteWriteFieldslem1RegisterFieldsField |
          WriteWriteFieldslem1RegisterFields.getValue()) {}
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsFieldType>
class ReadWriteFieldslege1
    : public ReadWrite<
          ReadWriteRegisterType,
          ReadWriteFieldslege1<
              ReadWriteRegisterType,
              ReadWriteReadWriteFieldslem1RegisterFieldsType,
              ReadWriteReadWriteFieldslem1RegisterFieldsFieldType>> {
  using ReadWriteFieldslege1Type = ReadWriteFieldslege1<
      ReadWriteRegisterType, ReadWriteReadWriteFieldslem1RegisterFieldsType,
      ReadWriteReadWriteFieldslem1RegisterFieldsFieldType>;
  using ReadWriteType =
      ReadWrite<ReadWriteRegisterType, ReadWriteFieldslege1Type>;
  friend ReadWriteType;
  static constexpr auto InverseMask{
      ~(ReadWriteReadWriteFieldslem1RegisterFieldsFieldType::getMask()) &
      ReadWriteReadWriteFieldslem1RegisterFieldsType::getInverseMask()};

protected:
  const ReadWriteReadWriteFieldslem1RegisterFieldsType
      &ReadWriteFieldslem1RegisterFields;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;
  const RegisterValueType V;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  auto getValue() const { return this->V; }

public:
  ReadWriteFieldslege1(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWriteFieldslem1RegisterFieldsType
          &ReadWriteReadWriteFieldslem1RegisterFields,
      const ReadWriteReadWriteFieldslem1RegisterFieldsFieldType
          ReadWriteReadWriteFieldslem1RegisterFieldsField)
      : ReadWriteType(ReadWriteRegister, ReadWriteRegisterValue),
        ReadWriteFieldslem1RegisterFields(
            ReadWriteReadWriteFieldslem1RegisterFields),
        V(ReadWriteReadWriteFieldslem1RegisterFieldsField |
          ReadWriteReadWriteFieldslem1RegisterFields.getValue()) {}
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1RegisterFieldsType,
          class WriteWriteFieldslem1RegisterFieldsFieldType,
          class WriteFieldType>
class WriteFieldslege1RegisterFields<
    WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
    WriteWriteFieldslem1RegisterFieldsType,
    WriteWriteFieldslem1RegisterFieldsFieldType, WriteFieldType>
    : public WriteFieldslege1<WriteRegisterType, false,
                              WriteRegisterResetValue,
                              WriteWriteFieldslem1RegisterFieldsType,
                              WriteWriteFieldslem1RegisterFieldsFieldType> {
  using WriteFieldslege1RegisterFieldsType = WriteFieldslege1RegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteWriteFieldslem1RegisterFieldsType,
      WriteWriteFieldslem1RegisterFieldsFieldType, WriteFieldType>;
  template <bool MightAllFieldsBeWritten>
  using WriteFieldslep1Type =
      WriteFieldslege1<WriteRegisterType, MightAllFieldsBeWritten,
                       WriteRegisterResetValue,
                       WriteFieldslege1RegisterFieldsType, WriteFieldType>;
  friend WriteFieldslep1Type<WriteMightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1Type =
      WriteFieldslege1<WriteRegisterType, false, WriteRegisterResetValue,
                       WriteWriteFieldslem1RegisterFieldsType,
                       WriteWriteFieldslem1RegisterFieldsFieldType>;

protected:
  using WriteFieldslege1Type::getInverseMask;
  using WriteFieldslege1Type::getValue;

public:
  using WriteFieldslege1Type::write;

  WriteFieldslege1RegisterFields(
      const WriteRegisterType &WriteRegister,
      const WriteWriteFieldslem1RegisterFieldsType
          &WriteWriteFieldslem1RegisterFields,
      const WriteWriteFieldslem1RegisterFieldsFieldType
          WriteWriteFieldslem1RegisterFieldsField)
      : WriteFieldslege1Type(WriteRegister, WriteWriteFieldslem1RegisterFields,
                             WriteWriteFieldslem1RegisterFieldsField) {}

  auto write(const WriteFieldType F) const {
    return WriteFieldslep1Type<WriteMightAllFieldsBeWritten>(this->R, *this,
                                                             F);
  }
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsFieldType,
          class ReadWriteFieldType>
class ReadWriteFieldslege1RegisterFields<
    ReadWriteRegisterType, ReadWriteReadWriteFieldslem1RegisterFieldsType,
    ReadWriteReadWriteFieldslem1RegisterFieldsFieldType, ReadWriteFieldType>
    : public ReadWriteFieldslege1<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1RegisterFieldsType,
          ReadWriteReadWriteFieldslem1RegisterFieldsFieldType> {
  using ReadWriteFieldslege1RegisterFieldsType =
      ReadWriteFieldslege1RegisterFields<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1RegisterFieldsType,
          ReadWriteReadWriteFieldslem1RegisterFieldsFieldType,
          ReadWriteFieldType>;
  using ReadWriteFieldslep1Type =
      ReadWriteFieldslege1<ReadWriteRegisterType,
                           ReadWriteFieldslege1RegisterFieldsType,
                           ReadWriteFieldType>;
  friend ReadWriteFieldslep1Type;
  using ReadWriteFieldslege1Type = ReadWriteFieldslege1<
      ReadWriteRegisterType, ReadWriteReadWriteFieldslem1RegisterFieldsType,
      ReadWriteReadWriteFieldslem1RegisterFieldsFieldType>;

protected:
  using ReadWriteFieldslege1Type::getInverseMask;
  using ReadWriteFieldslege1Type::getValue;

public:
  using ReadWriteFieldslege1Type::write;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;

public:
  ReadWriteFieldslege1RegisterFields(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWriteFieldslem1RegisterFieldsType
          &ReadWriteReadWriteFieldslem1RegisterFields,
      const ReadWriteReadWriteFieldslem1RegisterFieldsFieldType
          ReadWriteReadWriteFieldslem1RegisterFieldsField)
      : ReadWriteFieldslege1Type(
            ReadWriteRegister, ReadWriteRegisterValue,
            ReadWriteReadWriteFieldslem1RegisterFields,
            ReadWriteReadWriteFieldslem1RegisterFieldsField) {}

  auto write(const ReadWriteFieldType F) const {
    return ReadWriteFieldslep1Type(this->R, this->RegisterValue, *this, F);
  }
};

template <class WriteRegisterType, bool WriteMightAllFieldsBeWritten,
          typename WriteRegisterType::ValueType WriteRegisterResetValue,
          class WriteWriteFieldslem1RegisterFieldsType,
          class WriteWriteFieldslem1RegisterFieldsFieldType,
          class WriteFieldType, class... WriteFieldsgep1Types>
class WriteFieldslege1RegisterFields
    : public WriteFieldslege1RegisterFields<
          WriteRegisterType, false, WriteRegisterResetValue,
          WriteWriteFieldslem1RegisterFieldsType,
          WriteWriteFieldslem1RegisterFieldsFieldType,
          WriteFieldsgep1Types...> {
  using WriteFieldslege1RegisterFieldsType = WriteFieldslege1RegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteWriteFieldslem1RegisterFieldsType,
      WriteWriteFieldslem1RegisterFieldsFieldType, WriteFieldType,
      WriteFieldsgep1Types...>;
  template <bool MightAllFieldsBeWritten>
  using WriteFieldslep1Type =
      WriteFieldslege1<WriteRegisterType, MightAllFieldsBeWritten,
                       WriteRegisterResetValue,
                       WriteFieldslege1RegisterFieldsType, WriteFieldType>;
  friend WriteFieldslep1Type<WriteMightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1RegisterFieldsgep1Type =
      WriteFieldslege1RegisterFields<
          WriteRegisterType, false, WriteRegisterResetValue,
          WriteWriteFieldslem1RegisterFieldsType,
          WriteWriteFieldslem1RegisterFieldsFieldType,
          WriteFieldsgep1Types...>;

protected:
  using WriteFieldslege1RegisterFieldsgep1Type::getInverseMask;
  using WriteFieldslege1RegisterFieldsgep1Type::getValue;

public:
  using WriteFieldslege1RegisterFieldsgep1Type::write;

  WriteFieldslege1RegisterFields(
      const WriteRegisterType &WriteRegister,
      const WriteWriteFieldslem1RegisterFieldsType
          &WriteWriteFieldslem1RegisterFields,
      const WriteWriteFieldslem1RegisterFieldsFieldType
          WriteWriteFieldslem1RegisterFieldsField)
      : WriteFieldslege1RegisterFieldsgep1Type(
            WriteRegister, WriteWriteFieldslem1RegisterFields,
            WriteWriteFieldslem1RegisterFieldsField) {}

private:
  using WriteFieldslep1RegisterFieldsType = WriteFieldslege1RegisterFields<
      WriteRegisterType, WriteMightAllFieldsBeWritten, WriteRegisterResetValue,
      WriteFieldslege1RegisterFieldsType, WriteFieldType,
      WriteFieldsgep1Types...>;

public:
  auto write(const WriteFieldType F) const {
    return WriteFieldslep1RegisterFieldsType(this->R, *this, F);
  }
};

template <class ReadWriteRegisterType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsType,
          class ReadWriteReadWriteFieldslem1RegisterFieldsFieldType,
          class ReadWriteFieldType, class... ReadWriteFieldsgep1Types>
class ReadWriteFieldslege1RegisterFields
    : public ReadWriteFieldslege1RegisterFields<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1RegisterFieldsType,
          ReadWriteReadWriteFieldslem1RegisterFieldsFieldType,
          ReadWriteFieldsgep1Types...> {
  using ReadWriteFieldslege1RegisterFieldsType =
      ReadWriteFieldslege1RegisterFields<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1RegisterFieldsType,
          ReadWriteReadWriteFieldslem1RegisterFieldsFieldType,
          ReadWriteFieldType, ReadWriteFieldsgep1Types...>;
  friend ReadWriteFieldslege1<ReadWriteRegisterType,
                              ReadWriteFieldslege1RegisterFieldsType,
                              ReadWriteFieldType>;
  using ReadWriteFieldslege1RegisterFieldsgep1Type =
      ReadWriteFieldslege1RegisterFields<
          ReadWriteRegisterType,
          ReadWriteReadWriteFieldslem1RegisterFieldsType,
          ReadWriteReadWriteFieldslem1RegisterFieldsFieldType,
          ReadWriteFieldsgep1Types...>;

protected:
  using ReadWriteFieldslege1RegisterFieldsgep1Type::getInverseMask;
  using ReadWriteFieldslege1RegisterFieldsgep1Type::getValue;

public:
  using ReadWriteFieldslege1RegisterFieldsgep1Type::write;

private:
  using RegisterValueType = typename ReadWriteRegisterType::ValueType;

public:
  ReadWriteFieldslege1RegisterFields(
      const ReadWriteRegisterType &ReadWriteRegister,
      const RegisterValueType ReadWriteRegisterValue,
      const ReadWriteReadWriteFieldslem1RegisterFieldsType
          &ReadWriteReadWriteFieldslem1RegisterFields,
      const ReadWriteReadWriteFieldslem1RegisterFieldsFieldType
          ReadWriteReadWriteFieldslem1RegisterFieldsField)
      : ReadWriteFieldslege1RegisterFieldsgep1Type(
            ReadWriteRegister, ReadWriteRegisterValue,
            ReadWriteReadWriteFieldslem1RegisterFields,
            ReadWriteReadWriteFieldslem1RegisterFieldsField) {}

private:
  using ReadWriteFieldslep1RegisterFieldsType =
      ReadWriteFieldslege1RegisterFields<
          ReadWriteRegisterType, ReadWriteFieldslege1RegisterFieldsType,
          ReadWriteFieldType, ReadWriteFieldsgep1Types...>;

public:
  auto write(const ReadWriteFieldType F) const {
    return ReadWriteFieldslep1RegisterFieldsType(this->R, this->RegisterValue,
                                                 *this, F);
  }
};

} // namespace

template <class RegisterRegisterType,
          typename RegisterRegisterType::ValueType RegisterResetValue,
          class... RegisterFieldTypes>
class Register
    : public WriteRegisterFields<RegisterRegisterType, true,
                                 RegisterResetValue, RegisterFieldTypes...> {
  using WriteRegisterFieldsType =
      WriteRegisterFields<RegisterRegisterType, true, RegisterResetValue,
                          RegisterFieldTypes...>;

public:
  using WriteRegisterFieldsType::write;

  Register(const RegisterRegisterType &RegisterRegister)
      : WriteRegisterFieldsType(RegisterRegister) {}
};

} // namespace tiva

#endif // TIVA_REGISTER_REGISTER_H
