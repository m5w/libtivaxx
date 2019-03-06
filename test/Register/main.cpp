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

#include <tiva/Register/Field.h>
#include <tiva/Register/MemorymappedRegister.h>
#include <tiva/Register/Register.h>

class Nibble0Field : public tiva::Field<std::uint32_t, 0x00, 0x03> {
  using BasicField = tiva::Field<std::uint32_t, 0x00, 0x03>;

public:
  constexpr Nibble0Field(const std::uint32_t Value) : BasicField(Value) {}
};

class Nibble1Field : public tiva::Field<std::uint32_t, 0x04, 0x07> {
  using BasicField = tiva::Field<std::uint32_t, 0x04, 0x07>;

public:
  constexpr Nibble1Field(const std::uint32_t Value) : BasicField(Value) {}
};

class Nibble2Field : public tiva::Field<std::uint32_t, 0x08, 0x0b> {
  using BasicField = tiva::Field<std::uint32_t, 0x08, 0x0b>;

public:
  constexpr Nibble2Field(const std::uint32_t Value) : BasicField(Value) {}
};

class Nibble3Field : public tiva::Field<std::uint32_t, 0x0c, 0x0f> {
  using BasicField = tiva::Field<std::uint32_t, 0x0c, 0x0f>;

public:
  constexpr Nibble3Field(const std::uint32_t Value) : BasicField(Value) {}
};

class Nibble4Field : public tiva::Field<std::uint32_t, 0x10, 0x13> {
  using BasicField = tiva::Field<std::uint32_t, 0x10, 0x13>;

public:
  constexpr Nibble4Field(const std::uint32_t Value) : BasicField(Value) {}
};

extern volatile std::uint32_t A;

extern "C" void main() {
  constexpr tiva::MemorymappedRegister<std::uint32_t> BasicRegister0(
      reinterpret_cast<std::uint32_t>(&A));
  tiva::Register<decltype(BasicRegister0), 0x00'00'00'00u, Nibble0Field,
                 Nibble1Field, Nibble2Field, Nibble3Field, Nibble4Field>
      Register0(BasicRegister0);

  // # Paths
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
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>()).write();

  // 1
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>()).write();

  // 2
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>()).write();

  // 3
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>()).write();

  // 4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>()).write();

  // # Paths
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
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write();

  // 0-2
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write();

  // 0-3
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write();

  // 0-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // 1-2
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write();

  // 1-3
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write();

  // 1-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // 2-3
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write();

  // 2-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // 3-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // # Paths
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
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write();

  // 0-1-3
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write();

  // 0-1-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // 0-2-3
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write();

  // 0-2-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // 0-3-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // 1-2-3
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write();

  // 1-2-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // 1-3-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // 2-3-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // # Paths
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
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write();

  // * 0-1-2-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // * 0-1-3-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // * 0-2-3-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // * 1-2-3-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  // # Paths
  // * 0-1-2-3-4
  //
  // **Total**: 1 path
  //
  // 5 choose 5 = 5! / (5! * 0!) = 1 path

  // 0-1-2-3-4
  A = 0xff'ff'ff'ffu;
  Register0.write(tiva::makeField<Nibble0Field, 0x00'00'00'02u>())
      .write(tiva::makeField<Nibble1Field, 0x00'00'00'20u>())
      .write(tiva::makeField<Nibble2Field, 0x00'00'02'00u>())
      .write(tiva::makeField<Nibble3Field, 0x00'00'20'00u>())
      .write(tiva::makeField<Nibble4Field, 0x00'02'00'00u>())
      .write();

  for (;;)
    ;
}

volatile std::uint32_t A{0x00'00'00'00u};
