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

#ifndef TIVA_REGISTER_ROMEMORYMAPPEDREGISTER_H
#define TIVA_REGISTER_ROMEMORYMAPPEDREGISTER_H

#include <cstdint>

#include "tiva/Register/ReadableMemorymappedRegister.h"

namespace tiva {

template <class RegisterValueType>
class RoMemorymappedRegister
    : public detail::ReadableMemorymappedRegister<RegisterValueType> {
public:
  using ValueType = RegisterValueType;

private:
  using ReadableMemorymappedRegisterType =
      detail::ReadableMemorymappedRegister<ValueType>;

public:
  constexpr explicit RoMemorymappedRegister(
      const std::uint32_t RegisterAddress)
      : ReadableMemorymappedRegisterType(RegisterAddress) {}

  constexpr bool operator==(const RoMemorymappedRegister &RhandSide) const {
    return ReadableMemorymappedRegisterType::operator==(RhandSide);
  }
};

} // namespace tiva

#endif // TIVA_REGISTER_ROMEMORYMAPPEDREGISTER_H
