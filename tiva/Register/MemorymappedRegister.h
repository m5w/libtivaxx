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

template <class RegisterValueType> class MemorymappedRegister;

template <class RegisterValueType>
bool operator==(const MemorymappedRegister<RegisterValueType> &LhandSide,
                const MemorymappedRegister<RegisterValueType> &RhandSide) {
  return LhandSide.Address == RhandSide.Address;
}

template <class RegisterValueType> class MemorymappedRegister {
public:
  using ValueType = RegisterValueType;

protected:
  std::uint32_t Address;

public:
  constexpr MemorymappedRegister(const std::uint32_t RegisterAddress)
      : Address(RegisterAddress) {}

  friend bool operator==<>(const MemorymappedRegister &LhandSide,
                           const MemorymappedRegister &RhandSide);

  auto read() const {
    return *reinterpret_cast<const volatile ValueType *>(this->Address);
  }

  void write(const ValueType RegisterValue) const {
    *reinterpret_cast<volatile ValueType *>(this->Address) = RegisterValue;
  }
};

} // namespace tiva

#endif // TIVA_REGISTER_MEMORYMAPPEDREGISTER_H
