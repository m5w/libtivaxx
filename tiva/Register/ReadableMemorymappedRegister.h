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

#ifndef TIVA_REGISTER_READABLEMEMORYMAPPEDREGISTER_H
#define TIVA_REGISTER_READABLEMEMORYMAPPEDREGISTER_H

#include <cstdint>

#include "tiva/Register/MemorymappedRegister.h"

namespace tiva {

namespace detail {

template <class RegisterValueType> class ReadableMemorymappedRegister;

template <class RegisterValueType>
class ReadableMemorymappedRegister
    : public MemorymappedRegister<RegisterValueType> {
  using ValueType = RegisterValueType;
  using MemorymappedRegisterType = MemorymappedRegister<ValueType>;

public:
  constexpr explicit ReadableMemorymappedRegister(
      const std::uint32_t RegisterAddress)
      : MemorymappedRegisterType(RegisterAddress) {}

  auto read() const {
    return *reinterpret_cast<const volatile ValueType *>(this->Address);
  }
};

} // namespace detail

} // namespace tiva

#endif // TIVA_REGISTER_READABLEMEMORYMAPPEDREGISTER_H
