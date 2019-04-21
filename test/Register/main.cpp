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

#include <cassert>
#include <cstdint>

#include <tiva/Field/DerivedField.h>
#include <tiva/Field/Field.h>
#include <tiva/Register/MemorymappedRegister.h>
#include <tiva/Register/Register.h>
#include <tiva/Register/RegisterField.h>

using NibbleField = tiva::DerivedField<tiva::Field<std::uint32_t, 0x04>>;

using Nibble0Field = tiva::RegisterField<NibbleField::FieldType, 0x00>;
using Nibble1Field = tiva::RegisterField<NibbleField::FieldType, 0x04>;
using Nibble2Field = tiva::RegisterField<NibbleField::FieldType, 0x08>;
using Nibble3Field = tiva::RegisterField<NibbleField::FieldType, 0x0c>;
using Nibble4Field = tiva::RegisterField<NibbleField::FieldType, 0x10>;

static volatile std::uint32_t A;

extern "C" void main() {
  tiva::MemorymappedRegister<std::uint32_t> BaseRegister(
      reinterpret_cast<std::uint32_t>(&A));
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field>
      Register00(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0xff'ff'ff'ffu, Nibble0Field>
      Register01(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field,
                 Nibble1Field>
      Register10(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0xff'ff'ff'ffu, Nibble0Field,
                 Nibble1Field>
      Register11(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field,
                 Nibble1Field, Nibble2Field>
      Register20(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0xff'ff'ff'ffu, Nibble0Field,
                 Nibble1Field, Nibble2Field>
      Register21(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field,
                 Nibble1Field, Nibble2Field, Nibble3Field>
      Register30(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0xff'ff'ff'ffu, Nibble0Field,
                 Nibble1Field, Nibble2Field, Nibble3Field>
      Register31(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0x00'00'00'00u, Nibble0Field,
                 Nibble1Field, Nibble2Field, Nibble3Field, Nibble4Field>
      Register40(BaseRegister);
  tiva::Register<decltype(BaseRegister), 0xff'ff'ff'ffu, Nibble0Field,
                 Nibble1Field, Nibble2Field, Nibble3Field, Nibble4Field>
      Register41(BaseRegister);

  // # 1-Field Register

  A = 0xff'ff'ff'ffu;
  const auto &Register00ReadRRegisterFields{[&] {
    Nibble0Field::ReadRegisterFieldType N0F(0x00'00'00'00u);
    const auto &R00RRRF{Register00.read(N0F)};
    assert(N0F == 0x00'00'00'0fu);
    return R00RRRF;
  }()};
  assert(A == 0xff'ff'ff'ffu);
  assert([&] {
    Nibble0Field::ReadRegisterFieldType N0F(0x00'00'00'00u);
    const auto &R00RRRF{Register00.read(N0F)};
    assert(N0F == 0x00'00'00'0fu);
    return R00RRRF;
  }() == Register00ReadRRegisterFields);
  assert(A == 0xff'ff'ff'ffu);
  A = 0x00'00'00'00u;
  const auto &Register01ReadRRegisterFields{[&] {
    Nibble0Field::ReadRegisterFieldType N0F(0x00'00'00'0fu);
    const auto &R01RRRF{Register01.read(N0F)};
    assert(N0F == 0x00'00'00'00u);
    return R01RRRF;
  }()};
  assert(A == 0x00'00'00'00u);
  assert([&] {
    Nibble0Field::ReadRegisterFieldType N0F(0x00'00'00'0fu);
    const auto &R01RRRF{Register01.read(N0F)};
    assert(N0F == 0x00'00'00'00u);
    return R01RRRF;
  }() == Register01ReadRRegisterFields);

  // ## 1-Field Paths
  // * 0
  //
  // **Total**: 1 path
  //
  // 1 choose 1 = 1! / (1! * 0!) = 1 path

  // 0
  A = 0xff'ff'ff'ffu;
  Register00ReadRRegisterFields.write(Nibble0Field::make<0x0u>()).write();
  assert(A == 0xff'ff'ff'f0u);
  A = 0x00'00'00'00u;
  Register01ReadRRegisterFields.write(Nibble0Field::make<0xfu>()).write();
  assert(A == 0x00'00'00'0fu);
  A = 0xff'ff'ff'ffu;
  Register00.write(Nibble0Field::make<0xfu>()).write();
  assert(A == 0x00'00'00'0fu);
  A = 0x00'00'00'00u;
  Register01.write(Nibble0Field::make<0x0u>()).write();
  assert(A == 0xff'ff'ff'f0u);

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
  Register10.write(Nibble0Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'f1u);
  A = 0xff'ff'ff'ffu;
  Register10.read().write(Nibble0Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'f1u);

  // 1
  A = 0xff'ff'ff'ffu;
  Register10.write(Nibble1Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'1fu);
  A = 0xff'ff'ff'ffu;
  Register10.read().write(Nibble1Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'1fu);

  // ## 2-Field Paths
  // * 0-1
  //
  // **Total**: 1 path
  //
  // 2 choose 2 = 2! / (2! * 0!) = 1 path

  // 0-1
  A = 0xff'ff'ff'ffu;
  Register10.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write();
  assert(A == 0x00'00'00'11u);
  A = 0xff'ff'ff'ffu;
  Register10.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'ff'11u);

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
  Register20.write(Nibble0Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'f1u);
  A = 0xff'ff'ff'ffu;
  Register20.read().write(Nibble0Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'f1u);

  // 1
  A = 0xff'ff'ff'ffu;
  Register20.write(Nibble1Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'1fu);
  A = 0xff'ff'ff'ffu;
  Register20.read().write(Nibble1Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'1fu);

  // 2
  A = 0xff'ff'ff'ffu;
  Register20.write(Nibble2Field::make<0x1u>()).write();
  assert(A == 0xff'ff'f1'ffu);
  A = 0xff'ff'ff'ffu;
  Register20.read().write(Nibble2Field::make<0x1u>()).write();
  assert(A == 0xff'ff'f1'ffu);

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
  Register20.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'ff'11u);
  A = 0xff'ff'ff'ffu;
  Register20.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'ff'11u);

  // 0-2
  A = 0xff'ff'ff'ffu;
  Register20.write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'f1u);
  A = 0xff'ff'ff'ffu;
  Register20.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'f1u);

  // 1-2
  A = 0xff'ff'ff'ffu;
  Register20.write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'1fu);
  A = 0xff'ff'ff'ffu;
  Register20.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'1fu);

  // ## 3-Field Paths
  // * 0-1-2
  //
  // **Total**: 1 path
  //
  // 3 choose 3 = 3! / (3! * 0!) = 1 path

  // 0-1-2
  A = 0xff'ff'ff'ffu;
  Register20.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0x00'00'01'11u);
  A = 0xff'ff'ff'ffu;
  Register20.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'11u);

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
  Register30.write(Nibble0Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'f1u);
  A = 0xff'ff'ff'ffu;
  Register30.read().write(Nibble0Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'f1u);

  // 1
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble1Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'1fu);
  A = 0xff'ff'ff'ffu;
  Register30.read().write(Nibble1Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'1fu);

  // 2
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble2Field::make<0x1u>()).write();
  assert(A == 0xff'ff'f1'ffu);
  A = 0xff'ff'ff'ffu;
  Register30.read().write(Nibble2Field::make<0x1u>()).write();
  assert(A == 0xff'ff'f1'ffu);

  // 3
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble3Field::make<0x1u>()).write();
  assert(A == 0xff'ff'1f'ffu);
  A = 0xff'ff'ff'ffu;
  Register30.read().write(Nibble3Field::make<0x1u>()).write();
  assert(A == 0xff'ff'1f'ffu);

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
  Register30.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'ff'11u);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'ff'11u);

  // 0-2
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'f1u);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'f1u);

  // 0-3
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble0Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'f1u);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'f1u);

  // 1-2
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'1fu);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'1fu);

  // 1-3
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'1fu);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'1fu);

  // 2-3
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'ffu);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'ffu);

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
  Register30.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'11u);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'11u);

  // 0-1-3
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'11u);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'11u);

  // 0-2-3
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'f1u);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'f1u);

  // 1-2-3
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'1fu);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'1fu);

  // ## 4-Field Paths
  // * 0-1-2-3
  //
  // **Total**: 1 path
  //
  // 4 choose 4 = 4! / (4! * 0!) = 1 path

  // 0-1-2-3
  A = 0xff'ff'ff'ffu;
  Register30.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0x00'00'11'11u);
  A = 0xff'ff'ff'ffu;
  Register30.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'11u);

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
  Register40.write(Nibble0Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'f1u);
  A = 0xff'ff'ff'ffu;
  Register40.read().write(Nibble0Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'f1u);

  // 1
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble1Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'1fu);
  A = 0xff'ff'ff'ffu;
  Register40.read().write(Nibble1Field::make<0x1u>()).write();
  assert(A == 0xff'ff'ff'1fu);

  // 2
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble2Field::make<0x1u>()).write();
  assert(A == 0xff'ff'f1'ffu);
  A = 0xff'ff'ff'ffu;
  Register40.read().write(Nibble2Field::make<0x1u>()).write();
  assert(A == 0xff'ff'f1'ffu);

  // 3
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble3Field::make<0x1u>()).write();
  assert(A == 0xff'ff'1f'ffu);
  A = 0xff'ff'ff'ffu;
  Register40.read().write(Nibble3Field::make<0x1u>()).write();
  assert(A == 0xff'ff'1f'ffu);

  // 4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble4Field::make<0x1u>()).write();
  assert(A == 0xff'f1'ff'ffu);
  A = 0xff'ff'ff'ffu;
  Register40.read().write(Nibble4Field::make<0x1u>()).write();
  assert(A == 0xff'f1'ff'ffu);

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
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'ff'11u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'ff'11u);

  // 0-2
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'f1u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'f1u);

  // 0-3
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'f1u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'f1u);

  // 0-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'ff'f1u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'ff'f1u);

  // 1-2
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'1fu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'1fu);

  // 1-3
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'1fu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'1fu);

  // 1-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble1Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'ff'1fu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'ff'1fu);

  // 2-3
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'ffu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'ffu);

  // 2-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble2Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'f1'ffu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'f1'ffu);

  // 3-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'1f'ffu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'1f'ffu);

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
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'11u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'f1'11u);

  // 0-1-3
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'11u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'1f'11u);

  // 0-1-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'ff'11u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'ff'11u);

  // 0-2-3
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'f1u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'f1u);

  // 0-2-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'f1'f1u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'f1'f1u);

  // 0-3-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'1f'f1u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'1f'f1u);

  // 1-2-3
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'1fu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'1fu);

  // 1-2-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'f1'1fu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'f1'1fu);

  // 1-3-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'1f'1fu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'1f'1fu);

  // 2-3-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'11'ffu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'11'ffu);

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
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'11u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write();
  assert(A == 0xff'ff'11'11u);

  // * 0-1-2-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'f1'11u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'f1'11u);

  // * 0-1-3-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'1f'11u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'1f'11u);

  // * 0-2-3-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'11'f1u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'11'f1u);

  // * 1-2-3-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'11'1fu);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'11'1fu);

  // ## 5-Field Paths
  // * 0-1-2-3-4
  //
  // **Total**: 1 path
  //
  // 5 choose 5 = 5! / (5! * 0!) = 1 path

  // 0-1-2-3-4
  A = 0xff'ff'ff'ffu;
  Register40.write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0x00'01'11'11u);
  A = 0xff'ff'ff'ffu;
  Register40.read()
      .write(Nibble0Field::make<0x1u>())
      .write(Nibble1Field::make<0x1u>())
      .write(Nibble2Field::make<0x1u>())
      .write(Nibble3Field::make<0x1u>())
      .write(Nibble4Field::make<0x1u>())
      .write();
  assert(A == 0xff'f1'11'11u);

  for (;;)
    ;
}
