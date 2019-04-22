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

#ifndef TIVA_REGISTER_RWMEMORYMAPPEDREGISTER_H
#define TIVA_REGISTER_RWMEMORYMAPPEDREGISTER_H

#include <cstdint>

#include "tiva/Register/ReadableMemorymappedRegister.h"
#include "tiva/Register/WriteableMemorymappedRegister.h"

namespace tiva {

template <class RegisterValueType>
class RwMemorymappedRegister
    : public detail::ReadableMemorymappedRegister<RegisterValueType>,
      public detail::WriteableMemorymappedRegister<RegisterValueType> {
public:
  using ValueType = RegisterValueType;

private:
  using ReadableMemorymappedRegisterType =
      detail::ReadableMemorymappedRegister<ValueType>;
  using WriteableMemorymappedRegisterType =
      detail::WriteableMemorymappedRegister<ValueType>;

public:
  constexpr explicit RwMemorymappedRegister(
      const std::uint32_t RegisterAddress)
      : ReadableMemorymappedRegisterType(RegisterAddress),
        WriteableMemorymappedRegisterType(RegisterAddress) {}

  constexpr bool operator==(const RwMemorymappedRegister &RhandSide) const {
    return ReadableMemorymappedRegisterType::operator==(
               static_cast<const ReadableMemorymappedRegisterType &>(
                   RhandSide)) &&
           WriteableMemorymappedRegisterType::operator==(
               static_cast<const WriteableMemorymappedRegisterType &>(
                   RhandSide));
  }
};

} // namespace tiva

#endif // TIVA_REGISTER_RWMEMORYMAPPEDREGISTER_H
