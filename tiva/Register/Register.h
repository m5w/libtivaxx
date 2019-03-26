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

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue, class FieldType,
          class... FieldTypesgep1>
class WriteRegisterFields;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFields>
class Write;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class RegisterFieldm1, class RegisterFieldm1FieldType>
class WriteField0;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class RegisterFieldm1, class RegisterFieldm1FieldType,
          class FieldType, class... FieldTypesgep1>
class WriteField0RegisterFields;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1FieldType>
class WriteFieldslege1;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1FieldType,
          class FieldType, class... FieldTypesgep1>
class WriteFieldslege1RegisterFields;

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue, class FieldType>
class WriteRegisterFields<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, FieldType> {
protected:
  const BaseRegister &BR;

public:
  WriteRegisterFields(const BaseRegister &BR) : BR(BR) {}

private:
  using WriteRegisterFieldsType =
      WriteRegisterFields<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, FieldType>;
  using WriteField0Type =
      WriteField0<BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
                  WriteRegisterFieldsType, FieldType>;

public:
  auto write(const FieldType F) const { return WriteField0Type(this->BR, F); }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue, class FieldType,
          class... FieldTypesgep1>
class WriteRegisterFields
    : public WriteRegisterFields<BaseRegister, false, RegisterResetValue,
                                 FieldTypesgep1...> {
  using WriteRegisterFieldsgep1Type =
      WriteRegisterFields<BaseRegister, false, RegisterResetValue,
                          FieldTypesgep1...>;

public:
  using WriteRegisterFieldsgep1Type::write;

  WriteRegisterFields(const BaseRegister &BR)
      : WriteRegisterFieldsgep1Type(BR) {}

private:
  using WriteRegisterFieldsType =
      WriteRegisterFields<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, FieldType, FieldTypesgep1...>;
  using WriteField0RegisterFieldsType =
      WriteField0RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                RegisterResetValue, WriteRegisterFieldsType,
                                FieldType, FieldTypesgep1...>;

public:
  auto write(const FieldType F) const {
    return WriteField0RegisterFieldsType(this->BR, F);
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFields>
class Write {
protected:
  const BaseRegister &BR;

public:
  Write(const BaseRegister &BR) : BR(BR) {}

private:
  using BaseRegisterValue = typename BaseRegister::ValueType;

public:
  void write() const {
    BaseRegisterValue BRV;

    if constexpr (!MightAllFieldsBeWritten)
      BRV = this->BR.read();
    else
      BRV = RegisterResetValue;

    this->BR.write((BRV & WriteFields::getInverseMask()) |
                   static_cast<const WriteFields *>(this)->getValue());
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class RegisterFieldm1, class RegisterFieldm1FieldType>
class WriteField0
    : public Write<BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
                   WriteField0<BaseRegister, MightAllFieldsBeWritten,
                               RegisterResetValue, RegisterFieldm1,
                               RegisterFieldm1FieldType>> {
  using WriteField0Type =
      WriteField0<BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
                  RegisterFieldm1, RegisterFieldm1FieldType>;
  using WriteType = Write<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, WriteField0Type>;
  friend WriteType;
  static constexpr auto InverseMask{~(RegisterFieldm1FieldType::getMask())};
  using BaseRegisterValue = typename BaseRegister::ValueType;
  BaseRegisterValue Value;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  auto getValue() const { return this->Value; }

public:
  WriteField0(const BaseRegister &BR, const RegisterFieldm1FieldType RFm1F)
      : WriteType(BR), Value(RFm1F) {}
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class RegisterFieldm1, class RegisterFieldm1FieldType,
          class FieldType>
class WriteField0RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                RegisterResetValue, RegisterFieldm1,
                                RegisterFieldm1FieldType, FieldType>
    : public WriteField0<BaseRegister, false, RegisterResetValue,
                         RegisterFieldm1, RegisterFieldm1FieldType> {
  using WriteField0RegisterFieldsType =
      WriteField0RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                RegisterResetValue, RegisterFieldm1,
                                RegisterFieldm1FieldType, FieldType>;
  template <bool MAFBW>
  using WriteFieldsle1Type =
      WriteFieldslege1<BaseRegister, MAFBW, RegisterResetValue,
                       WriteField0RegisterFieldsType, FieldType>;
  friend WriteFieldsle1Type<MightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0Type =
      WriteField0<BaseRegister, false, RegisterResetValue, RegisterFieldm1,
                  RegisterFieldm1FieldType>;

protected:
  using WriteField0Type::getInverseMask;
  using WriteField0Type::getValue;

public:
  using WriteField0Type::write;

  WriteField0RegisterFields(const BaseRegister &BR,
                            const RegisterFieldm1FieldType RFm1F)
      : WriteField0Type(BR, RFm1F) {}

  auto write(const FieldType F) const {
    return WriteFieldsle1Type<MightAllFieldsBeWritten>(this->BR, *this, F);
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class RegisterFieldm1, class RegisterFieldm1FieldType,
          class FieldType, class... FieldTypesgep1>
class WriteField0RegisterFields
    : public WriteField0RegisterFields<
          BaseRegister, false, RegisterResetValue, RegisterFieldm1,
          RegisterFieldm1FieldType, FieldTypesgep1...> {
  using WriteField0RegisterFieldsType = WriteField0RegisterFields<
      BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
      RegisterFieldm1, RegisterFieldm1FieldType, FieldType, FieldTypesgep1...>;
  template <bool MAFBW>
  using WriteFieldsle1Type =
      WriteFieldslege1<BaseRegister, MAFBW, RegisterResetValue,
                       WriteField0RegisterFieldsType, FieldType>;
  friend WriteFieldsle1Type<MightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0RegisterFieldsgep1Type =
      WriteField0RegisterFields<BaseRegister, false, RegisterResetValue,
                                RegisterFieldm1, RegisterFieldm1FieldType,
                                FieldTypesgep1...>;

protected:
  using WriteField0RegisterFieldsgep1Type::getInverseMask;
  using WriteField0RegisterFieldsgep1Type::getValue;

public:
  using WriteField0RegisterFieldsgep1Type::write;

  WriteField0RegisterFields(const BaseRegister &BR,
                            const RegisterFieldm1FieldType RFm1F)
      : WriteField0RegisterFieldsgep1Type(BR, RFm1F) {}

private:
  using WriteFieldsle1RegisterFieldsType = WriteFieldslege1RegisterFields<
      BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
      WriteField0RegisterFieldsType, FieldType, FieldTypesgep1...>;

public:
  auto write(const FieldType F) const {
    return WriteFieldsle1RegisterFieldsType(this->BR, *this, F);
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1FieldType>
class WriteFieldslege1
    : public Write<BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
                   WriteFieldslege1<BaseRegister, MightAllFieldsBeWritten,
                                    RegisterResetValue, WriteFieldslem1,
                                    WriteFieldslem1FieldType>> {
  using WriteFieldslege1Type =
      WriteFieldslege1<BaseRegister, MightAllFieldsBeWritten,
                       RegisterResetValue, WriteFieldslem1,
                       WriteFieldslem1FieldType>;
  using WriteType = Write<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, WriteFieldslege1Type>;
  friend WriteType;
  static constexpr auto InverseMask{~(WriteFieldslem1FieldType::getMask()) &
                                    WriteFieldslem1::getInverseMask()};

protected:
  const WriteFieldslem1 &WFm1;

private:
  using BaseRegisterValue = typename BaseRegister::ValueType;
  BaseRegisterValue Value;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  auto getValue() const { return this->Value; }

public:
  WriteFieldslege1(const BaseRegister &BR, const WriteFieldslem1 &WFm1,
                   const WriteFieldslem1FieldType WFm1F)
      : WriteType(BR), WFm1(WFm1), Value(WFm1F | WFm1.getValue()) {}
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1FieldType,
          class FieldType>
class WriteFieldslege1RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                     RegisterResetValue, WriteFieldslem1,
                                     WriteFieldslem1FieldType, FieldType>
    : public WriteFieldslege1<BaseRegister, false, RegisterResetValue,
                              WriteFieldslem1, WriteFieldslem1FieldType> {
  using WriteFieldslege1RegisterFieldsType =
      WriteFieldslege1RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                     RegisterResetValue, WriteFieldslem1,
                                     WriteFieldslem1FieldType, FieldType>;
  template <bool MAFBW>
  using WriteFieldslep1Type =
      WriteFieldslege1<BaseRegister, MAFBW, RegisterResetValue,
                       WriteFieldslege1RegisterFieldsType, FieldType>;
  friend WriteFieldslep1Type<MightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1Type =
      WriteFieldslege1<BaseRegister, false, RegisterResetValue,
                       WriteFieldslem1, WriteFieldslem1FieldType>;

protected:
  using WriteFieldslege1Type::getInverseMask;
  using WriteFieldslege1Type::getValue;

public:
  using WriteFieldslege1Type::write;

  WriteFieldslege1RegisterFields(const BaseRegister &BR,
                                 const WriteFieldslem1 &WFm1,
                                 const WriteFieldslem1FieldType WFm1F)
      : WriteFieldslege1Type(BR, WFm1, WFm1F) {}

  auto write(const FieldType F) const {
    return WriteFieldslep1Type<MightAllFieldsBeWritten>(this->BR, *this, F);
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1FieldType,
          class FieldType, class... FieldTypesgep1>
class WriteFieldslege1RegisterFields
    : public WriteFieldslege1RegisterFields<
          BaseRegister, false, RegisterResetValue, WriteFieldslem1,
          WriteFieldslem1FieldType, FieldTypesgep1...> {
  using WriteFieldslege1RegisterFieldsType = WriteFieldslege1RegisterFields<
      BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
      WriteFieldslem1, WriteFieldslem1FieldType, FieldType, FieldTypesgep1...>;
  template <bool MAFBW>
  using WriteFieldslep1Type =
      WriteFieldslege1<BaseRegister, MAFBW, RegisterResetValue,
                       WriteFieldslege1RegisterFieldsType, FieldType>;
  friend WriteFieldslep1Type<MightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1RegisterFieldsgep1Type =
      WriteFieldslege1RegisterFields<BaseRegister, false, RegisterResetValue,
                                     WriteFieldslem1, WriteFieldslem1FieldType,
                                     FieldTypesgep1...>;

protected:
  using WriteFieldslege1RegisterFieldsgep1Type::getInverseMask;
  using WriteFieldslege1RegisterFieldsgep1Type::getValue;

public:
  using WriteFieldslege1RegisterFieldsgep1Type::write;

  WriteFieldslege1RegisterFields(const BaseRegister &BR,
                                 const WriteFieldslem1 &WFm1,
                                 const WriteFieldslem1FieldType WFm1F)
      : WriteFieldslege1RegisterFieldsgep1Type(BR, WFm1, WFm1F) {}

private:
  using WriteFieldslep1RegisterFieldsType = WriteFieldslege1RegisterFields<
      BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
      WriteFieldslege1RegisterFieldsType, FieldType, FieldTypesgep1...>;

public:
  auto write(const FieldType F) const {
    return WriteFieldslep1RegisterFieldsType(this->BR, *this, F);
  }
};

} // namespace

template <class BaseRegister,
          typename BaseRegister::ValueType RegisterResetValue,
          class... FieldTypes>
class Register
    : public WriteRegisterFields<BaseRegister, true, RegisterResetValue,
                                 FieldTypes...> {
  using WriteRegisterFieldsType =
      WriteRegisterFields<BaseRegister, true, RegisterResetValue,
                          FieldTypes...>;

public:
  using WriteRegisterFieldsType::write;

  Register(const BaseRegister &BR) : WriteRegisterFieldsType(BR) {}
};

} // namespace tiva

#endif // TIVA_REGISTER_REGISTER_H
