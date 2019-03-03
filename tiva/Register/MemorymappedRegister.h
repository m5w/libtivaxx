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

#ifndef TIVA_REGISTER_MEMORYMAPPEDREGISTER_H
#define TIVA_REGISTER_MEMORYMAPPEDREGISTER_H

#include <cstdint>

namespace tiva {

template <class Value> class MemorymappedRegister {
protected:
  std::uint32_t Address;

public:
  constexpr MemorymappedRegister(const std::uint32_t Address)
      : Address(Address) {}

  auto read() const {
    return *reinterpret_cast<const volatile Value *>(this->Address);
  }

  void write(const Value V) const {
    *reinterpret_cast<volatile Value *>(this->Address) = V;
  }

  using ValueType = Value;
};

} // namespace tiva

#endif // TIVA_REGISTER_MEMORYMAPPEDREGISTER_H
