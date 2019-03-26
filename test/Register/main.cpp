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

#include <cstdint>

#include <tiva/Field/Field.h>
#include <tiva/Register/MemorymappedRegister.h>
#include <tiva/Register/Register.h>
#include <tiva/Register/RegisterField.h>

class NibbleField : public tiva::BaseField<std::uint32_t> {
public:
  using ValueType = std::uint32_t;

private:
  using BaseFieldType = BaseField<ValueType>;
  using FieldType = tiva::Field<ValueType, 0x04>;

  constexpr explicit NibbleField(const FieldType FieldField)
      : BaseFieldType(FieldField) {}

public:
  static constexpr auto getMask() { return FieldType::getMask(); }

  static constexpr bool isValueValid(const ValueType FieldFieldValue) {
    return FieldType::isValueValid(FieldFieldValue);
  }

  template <std::uint32_t FieldFieldValue>
  static constexpr NibbleField make() {
    return NibbleField(FieldType::template make<FieldFieldValue>());
  }

  static NibbleField UNSAFE_make(const FieldType FieldField) {
    return NibbleField(FieldField);
  }
};

using Nibble0Field = tiva::RegisterField<NibbleField, 0x00>;
using Nibble1Field = tiva::RegisterField<NibbleField, 0x04>;
using Nibble2Field = tiva::RegisterField<NibbleField, 0x08>;
using Nibble3Field = tiva::RegisterField<NibbleField, 0x0c>;
using Nibble4Field = tiva::RegisterField<NibbleField, 0x10>;

extern volatile std::uint32_t A;

extern "C" void main() {
  constexpr tiva::MemorymappedRegister<std::uint32_t> BaseRegister(
      reinterpret_cast<std::uint32_t>(&A));
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field>
      Register0(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field,
                 Nibble1Field>
      Register1(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field,
                 Nibble1Field, Nibble2Field>
      Register2(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field,
                 Nibble1Field, Nibble2Field, Nibble3Field>
      Register3(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field,
                 Nibble1Field, Nibble2Field, Nibble3Field, Nibble4Field>
      Register4(BaseRegister);

  // # 1-Field Register

  // ## 1-Field Paths
  // * 0
  //
  // **Total**: 1 path
  //
  // 1 choose 1 = 1! / (1! * 0!) = 1 path

  // 0
  A = 0xff'ff'ff'ffu;
  Register0.write(Nibble0Field::template make<0x1u>()).write();

  // # 2-Field Register

  // ## 1-Field Paths
  // * 0
  // * 1
  //
  // **Total**: 2 paths
  //
  // 2 choose 1 = 2! / (1! * 1!) = 2 paths

  // 0
  A = 0xff'ff'ff'ffu;
  Register1.write(Nibble0Field::template make<0x1u>()).write();

  // 1
  A = 0xff'ff'ff'ffu;
  Register1.write(Nibble1Field::template make<0x1u>()).write();

  // ## 2-Field Paths
  // * 0-1
  //
  // **Total**: 1 path
  //
  // 2 choose 2 = 2! / (2! * 0!) = 1 path

  // 0-1
  A = 0xff'ff'ff'ffu;
  Register1.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write();

  // # 3-Field Register

  // ## 1-Field Paths
  // * 0
  // * 1
  // * 2
  //
  // **Total**: 3 paths
  //
  // 3 choose 1 = 3! / (1! * 2!) = 3 paths

  // 0
  A = 0xff'ff'ff'ffu;
  Register2.write(Nibble0Field::template make<0x1u>()).write();

  // 1
  A = 0xff'ff'ff'ffu;
  Register2.write(Nibble1Field::template make<0x1u>()).write();

  // 2
  A = 0xff'ff'ff'ffu;
  Register2.write(Nibble2Field::template make<0x1u>()).write();

  // ## 2-Field Paths
  // * 0-1
  // * 0-2
  // * 1-2
  //
  // **Total**: 3 paths
  //
  // 3 choose 2 = 3! / (2! * 1!) = 3 paths

  // 0-1
  A = 0xff'ff'ff'ffu;
  Register2.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write();

  // 0-2
  A = 0xff'ff'ff'ffu;
  Register2.write(Nibble0Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write();

  // 1-2
  A = 0xff'ff'ff'ffu;
  Register2.write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write();

  // ## 3-Field Paths
  // * 0-1-2
  //
  // **Total**: 1 path
  //
  // 3 choose 3 = 3! / (3! * 0!) = 1 path

  // 0-1-2
  A = 0xff'ff'ff'ffu;
  Register2.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write();

  // # 4-Field Register

  // ## 1-Field Paths
  // * 0
  // * 1
  // * 2
  // * 3
  //
  // **Total**: 4 paths
  //
  // 4 choose 1 = 4! / (1! * 3!) = 4 paths

  // 0
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble0Field::template make<0x1u>()).write();

  // 1
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble1Field::template make<0x1u>()).write();

  // 2
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble2Field::template make<0x1u>()).write();

  // 3
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble3Field::template make<0x1u>()).write();

  // ## 2-Field Paths
  // * 0-1
  // * 0-2
  // * 0-3
  // * 1-2
  // * 1-3
  // * 2-3
  //
  // **Total**: 6 paths
  //
  // 4 choose 2 = 4! / (2! * 2!) = 6 paths

  // 0-1
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write();

  // 0-2
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble0Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write();

  // 0-3
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble0Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 1-2
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write();

  // 1-3
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble1Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 2-3
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // ## 3-Field Paths
  // * 0-1-2
  // * 0-1-3
  // * 0-2-3
  // * 1-2-3
  //
  // **Total**: 4 paths
  //
  // 4 choose 3 = 4! / (3! * 1!) = 4 paths

  // 0-1-2
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write();

  // 0-1-3
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 0-2-3
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble0Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 1-2-3
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // ## 4-Field Paths
  // * 0-1-2-3
  //
  // **Total**: 1 path
  //
  // 4 choose 4 = 4! / (4! * 0!) = 1 path

  // 0-1-2-3
  A = 0xff'ff'ff'ffu;
  Register3.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // # 5-Field Register

  // ## 1-Field Paths
  // * 0
  // * 1
  // * 2
  // * 3
  // * 4
  //
  // **Total**: 5 paths
  //
  // 5 choose 1 = 5! / (1! * 4!) = 5

  // 0
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>()).write();

  // 1
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble1Field::template make<0x1u>()).write();

  // 2
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble2Field::template make<0x1u>()).write();

  // 3
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble3Field::template make<0x1u>()).write();

  // 4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble4Field::template make<0x1u>()).write();

  // ## 2-Field Paths
  // * 0-1
  // * 0-2
  // * 0-3
  // * 0-4
  // * 1-2
  // * 1-3
  // * 1-4
  // * 2-3
  // * 2-4
  // * 3-4
  //
  // **Total**: 10 paths
  //
  // 5 choose 2 = 5! / (2! * 3!) = 10 paths

  // 0-1
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write();

  // 0-2
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write();

  // 0-3
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 0-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // 1-2
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write();

  // 1-3
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble1Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 1-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble1Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // 2-3
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 2-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble2Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // 3-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble3Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // ## 3-Field Paths
  // * 0-1-2
  // * 0-1-3
  // * 0-1-4
  // * 0-2-3
  // * 0-2-4
  // * 0-3-4
  // * 1-2-3
  // * 1-2-4
  // * 1-3-4
  // * 2-3-4
  //
  // **Total**: 10 paths
  //
  // 5 choose 3 = 5! / (3! * 2!) = 10 paths

  // 0-1-2
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write();

  // 0-1-3
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 0-1-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // 0-2-3
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 0-2-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // 0-3-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // 1-2-3
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // 1-2-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // 1-3-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble1Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // 2-3-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // ## 4-Field Paths
  // * 0-1-2-3
  // * 0-1-2-4
  // * 0-1-3-4
  // * 0-2-3-4
  // * 1-2-3-4
  //
  // **Total**: 5 paths
  //
  // 5 choose 4 = 5! / (4! * 1!) = 5 paths

  // * 0-1-2-3
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write();

  // * 0-1-2-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // * 0-1-3-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // * 0-2-3-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // * 1-2-3-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  // ## 5-Field Paths
  // * 0-1-2-3-4
  //
  // **Total**: 1 path
  //
  // 5 choose 5 = 5! / (5! * 0!) = 1 path

  // 0-1-2-3-4
  A = 0xff'ff'ff'ffu;
  Register4.write(Nibble0Field::template make<0x1u>())
      .write(Nibble1Field::template make<0x1u>())
      .write(Nibble2Field::template make<0x1u>())
      .write(Nibble3Field::template make<0x1u>())
      .write(Nibble4Field::template make<0x1u>())
      .write();

  for (;;)
    ;
}

volatile std::uint32_t A{0x00u};
