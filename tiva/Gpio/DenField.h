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

#ifndef TIVA_GPIO_DENFIELD_H
#define TIVA_GPIO_DENFIELD_H

#include <cstdint>

#include "tiva/Field/EnumeratedField.h"
#include "tiva/Field/Field.h"

namespace tiva {

namespace detail {

class DenField : public EnumeratedField<Field<std::uint32_t, 1>> {
public:
  using FieldType = Field<std::uint32_t, 1>;

private:
  using EnumeratedFieldType = EnumeratedField<FieldType>;

  constexpr explicit DenField(const FieldType FieldField)
      : EnumeratedFieldType(FieldField) {}

  using FieldValueType = typename FieldType::ValueType;

public:
  using ValueType = FieldValueType;

  static constexpr auto Disabled() { return DenField(FieldType::make<0>()); }

  static constexpr auto Enabled() { return DenField(FieldType::make<1>()); }
};

} // namespace detail

} // namespace tiva

#endif // TIVA_GPIO_DENFIELD_H
