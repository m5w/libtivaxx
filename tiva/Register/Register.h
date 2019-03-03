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
          typename BaseRegister::ValueType RegisterResetValue, class BaseField,
          class... BaseFieldsgep1>
class WriteRegisterFields;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFields>
class Write;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class RegisterFieldm1, class RegisterFieldm1BaseField>
class WriteField0;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class RegisterFieldm1, class RegisterFieldm1BaseField,
          class BaseField, class... BaseFieldsgep1>
class WriteField0RegisterFields;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1BaseField>
class WriteFieldslege1;
template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1BaseField,
          class BaseField, class... BaseFieldsgep1>
class WriteFieldslege1RegisterFields;

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue, class BaseField>
class WriteRegisterFields<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, BaseField> {
protected:
  const BaseRegister &BR;

public:
  WriteRegisterFields(const BaseRegister &BR) : BR(BR) {}

private:
  using WriteRegisterFieldsType =
      WriteRegisterFields<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, BaseField>;
  using WriteField0Type =
      WriteField0<BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
                  WriteRegisterFieldsType, BaseField>;

public:
  auto write(const BaseField BF) const {
    return WriteField0Type(this->BR, BF);
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue, class BaseField,
          class... BaseFieldsgep1>
class WriteRegisterFields
    : public WriteRegisterFields<BaseRegister, false, RegisterResetValue,
                                 BaseFieldsgep1...> {
  using WriteRegisterFieldsgep1Type =
      WriteRegisterFields<BaseRegister, false, RegisterResetValue,
                          BaseFieldsgep1...>;

public:
  using WriteRegisterFieldsgep1Type::write;

  WriteRegisterFields(const BaseRegister &BR)
      : WriteRegisterFieldsgep1Type(BR) {}

private:
  using WriteRegisterFieldsType =
      WriteRegisterFields<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, BaseField, BaseFieldsgep1...>;
  using WriteField0RegisterFieldsType =
      WriteField0RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                RegisterResetValue, WriteRegisterFieldsType,
                                BaseField, BaseFieldsgep1...>;

public:
  auto write(const BaseField BF) const {
    return WriteField0RegisterFieldsType(this->BR, BF);
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
          class RegisterFieldm1, class RegisterFieldm1BaseField>
class WriteField0
    : public Write<BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
                   WriteField0<BaseRegister, MightAllFieldsBeWritten,
                               RegisterResetValue, RegisterFieldm1,
                               RegisterFieldm1BaseField>> {
  using WriteField0Type =
      WriteField0<BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
                  RegisterFieldm1, RegisterFieldm1BaseField>;
  using WriteType = Write<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, WriteField0Type>;
  friend WriteType;
  static constexpr auto InverseMask{~(RegisterFieldm1BaseField::getMask())};
  using BaseRegisterValue = typename BaseRegister::ValueType;
  BaseRegisterValue Value;

protected:
  static constexpr auto getInverseMask() { return InverseMask; }

  auto getValue() const { return this->Value; }

public:
  WriteField0(const BaseRegister &BR, const RegisterFieldm1BaseField RFm1BF)
      : WriteType(BR), Value(RFm1BF.getValue()) {}
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class RegisterFieldm1, class RegisterFieldm1BaseField,
          class BaseField>
class WriteField0RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                RegisterResetValue, RegisterFieldm1,
                                RegisterFieldm1BaseField, BaseField>
    : public WriteField0<BaseRegister, MightAllFieldsBeWritten,
                         RegisterResetValue, RegisterFieldm1,
                         RegisterFieldm1BaseField> {
  using WriteField0RegisterFieldsType =
      WriteField0RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                RegisterResetValue, RegisterFieldm1,
                                RegisterFieldm1BaseField, BaseField>;
  template <bool MAFBW>
  using WriteFieldsle1Type =
      WriteFieldslege1<BaseRegister, MAFBW, RegisterResetValue,
                       WriteField0RegisterFieldsType, BaseField>;
  friend WriteFieldsle1Type<MightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0Type =
      WriteField0<BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
                  RegisterFieldm1, RegisterFieldm1BaseField>;

protected:
  using WriteField0Type::getInverseMask;
  using WriteField0Type::getValue;

public:
  using WriteField0Type::write;

  WriteField0RegisterFields(const BaseRegister &BR,
                            const RegisterFieldm1BaseField RFm1BF)
      : WriteField0Type(BR, RFm1BF) {}

  auto write(const BaseField BF) const {
    return WriteFieldsle1Type<MightAllFieldsBeWritten>(this->BR, *this, BF);
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class RegisterFieldm1, class RegisterFieldm1BaseField,
          class BaseField, class... BaseFieldsgep1>
class WriteField0RegisterFields
    : public WriteField0RegisterFields<
          BaseRegister, false, RegisterResetValue, RegisterFieldm1,
          RegisterFieldm1BaseField, BaseFieldsgep1...> {
  using WriteField0RegisterFieldsType = WriteField0RegisterFields<
      BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
      RegisterFieldm1, RegisterFieldm1BaseField, BaseField, BaseFieldsgep1...>;
  template <bool MAFBW>
  using WriteFieldsle1Type =
      WriteFieldslege1<BaseRegister, MAFBW, RegisterResetValue,
                       WriteField0RegisterFieldsType, BaseField>;
  friend WriteFieldsle1Type<MightAllFieldsBeWritten>;
  friend WriteFieldsle1Type<false>;
  using WriteField0RegisterFieldsgep1Type =
      WriteField0RegisterFields<BaseRegister, false, RegisterResetValue,
                                RegisterFieldm1, RegisterFieldm1BaseField,
                                BaseFieldsgep1...>;

protected:
  using WriteField0RegisterFieldsgep1Type::getInverseMask;
  using WriteField0RegisterFieldsgep1Type::getValue;

public:
  using WriteField0RegisterFieldsgep1Type::write;

  WriteField0RegisterFields(const BaseRegister &BR,
                            const RegisterFieldm1BaseField RFm1BF)
      : WriteField0RegisterFieldsgep1Type(BR, RFm1BF) {}

private:
  using WriteFieldsle1RegisterFieldsType = WriteFieldslege1RegisterFields<
      BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
      WriteField0RegisterFieldsType, BaseField, BaseFieldsgep1...>;

public:
  auto write(const BaseField BF) const {
    return WriteFieldsle1RegisterFieldsType(this->BR, *this, BF);
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1BaseField>
class WriteFieldslege1
    : public Write<BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
                   WriteFieldslege1<BaseRegister, MightAllFieldsBeWritten,
                                    RegisterResetValue, WriteFieldslem1,
                                    WriteFieldslem1BaseField>> {
  using WriteFieldslege1Type =
      WriteFieldslege1<BaseRegister, MightAllFieldsBeWritten,
                       RegisterResetValue, WriteFieldslem1,
                       WriteFieldslem1BaseField>;
  using WriteType = Write<BaseRegister, MightAllFieldsBeWritten,
                          RegisterResetValue, WriteFieldslege1Type>;
  friend WriteType;
  static constexpr auto InverseMask{~(WriteFieldslem1BaseField::getMask()) &
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
                   const WriteFieldslem1BaseField WFm1BF)
      : WriteType(BR), WFm1(WFm1), Value(WFm1BF.getValue() | WFm1.getValue()) {
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1BaseField,
          class BaseField>
class WriteFieldslege1RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                     RegisterResetValue, WriteFieldslem1,
                                     WriteFieldslem1BaseField, BaseField>
    : public WriteFieldslege1<BaseRegister, MightAllFieldsBeWritten,
                              RegisterResetValue, WriteFieldslem1,
                              WriteFieldslem1BaseField> {
  using WriteFieldslege1RegisterFieldsType =
      WriteFieldslege1RegisterFields<BaseRegister, MightAllFieldsBeWritten,
                                     RegisterResetValue, WriteFieldslem1,
                                     WriteFieldslem1BaseField, BaseField>;
  template <bool MAFBW>
  using WriteFieldslep1Type =
      WriteFieldslege1<BaseRegister, MAFBW, RegisterResetValue,
                       WriteFieldslege1RegisterFieldsType, BaseField>;
  friend WriteFieldslep1Type<MightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1Type =
      WriteFieldslege1<BaseRegister, MightAllFieldsBeWritten,
                       RegisterResetValue, WriteFieldslem1,
                       WriteFieldslem1BaseField>;

protected:
  using WriteFieldslege1Type::getInverseMask;
  using WriteFieldslege1Type::getValue;

public:
  using WriteFieldslege1Type::write;

  WriteFieldslege1RegisterFields(const BaseRegister &BR,
                                 const WriteFieldslem1 &WFm1,
                                 const WriteFieldslem1BaseField WFm1BF)
      : WriteFieldslege1Type(BR, WFm1, WFm1BF) {}

  auto write(const BaseField BF) const {
    return WriteFieldslep1Type<MightAllFieldsBeWritten>(this->BR, *this, BF);
  }
};

template <class BaseRegister, bool MightAllFieldsBeWritten,
          typename BaseRegister::ValueType RegisterResetValue,
          class WriteFieldslem1, class WriteFieldslem1BaseField,
          class BaseField, class... BaseFieldsgep1>
class WriteFieldslege1RegisterFields
    : public WriteFieldslege1RegisterFields<
          BaseRegister, false, RegisterResetValue, WriteFieldslem1,
          WriteFieldslem1BaseField, BaseFieldsgep1...> {
  using WriteFieldslege1RegisterFieldsType = WriteFieldslege1RegisterFields<
      BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
      WriteFieldslem1, WriteFieldslem1BaseField, BaseField, BaseFieldsgep1...>;
  template <bool MAFBW>
  using WriteFieldslep1Type =
      WriteFieldslege1<BaseRegister, MAFBW, RegisterResetValue,
                       WriteFieldslege1RegisterFieldsType, BaseField>;
  friend WriteFieldslep1Type<MightAllFieldsBeWritten>;
  friend WriteFieldslep1Type<false>;
  using WriteFieldslege1RegisterFieldsgep1Type =
      WriteFieldslege1RegisterFields<BaseRegister, false, RegisterResetValue,
                                     WriteFieldslem1, WriteFieldslem1BaseField,
                                     BaseFieldsgep1...>;

protected:
  using WriteFieldslege1RegisterFieldsgep1Type::getInverseMask;
  using WriteFieldslege1RegisterFieldsgep1Type::getValue;

public:
  using WriteFieldslege1RegisterFieldsgep1Type::write;

  WriteFieldslege1RegisterFields(const BaseRegister &BR,
                                 const WriteFieldslem1 &WFm1,
                                 const WriteFieldslem1BaseField WFm1BF)
      : WriteFieldslege1RegisterFieldsgep1Type(BR, WFm1, WFm1BF) {}

private:
  using WriteFieldslep1RegisterFieldsType = WriteFieldslege1RegisterFields<
      BaseRegister, MightAllFieldsBeWritten, RegisterResetValue,
      WriteFieldslege1RegisterFieldsType, BaseField, BaseFieldsgep1...>;

public:
  auto write(const BaseField BF) const {
    return WriteFieldslep1RegisterFieldsType(this->BR, *this, BF);
  }
};

} // namespace

template <class BaseRegister,
          typename BaseRegister::ValueType RegisterResetValue,
          class... BaseFields>
class Register
    : public WriteRegisterFields<BaseRegister, true, RegisterResetValue,
                                 BaseFields...> {
  using WriteRegisterFieldsType =
      WriteRegisterFields<BaseRegister, true, RegisterResetValue,
                          BaseFields...>;

public:
  using WriteRegisterFieldsType::write;

  Register(const BaseRegister &BR) : WriteRegisterFieldsType(BR) {}
};

} // namespace tiva

#endif // TIVA_REGISTER_REGISTER_H
