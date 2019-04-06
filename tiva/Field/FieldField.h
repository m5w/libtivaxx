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

#ifndef TIVA_FIELD_FIELDFIELD_H
#define TIVA_FIELD_FIELDFIELD_H

namespace tiva {

template <class FieldFieldType, class FieldIsValueValidType>
class FieldField : public BaseField<typename FieldFieldType::ValueType> {
public:
  using ValueType = typename FieldFieldType::ValueType;

private:
  using BaseFieldType = BaseField<ValueType>;

  constexpr explicit FieldField(const FieldFieldType FieldFieldField)
      : BaseFieldType(FieldFieldField) {}

public:
  static constexpr auto getMask() { return FieldFieldType::getMask(); }

  static constexpr bool isValueValid(const ValueType FieldFieldFieldValue) {
    constexpr FieldIsValueValidType IsValueValid;
    return FieldFieldType::isValueValid(FieldFieldFieldValue) &&
           IsValueValid(FieldFieldFieldValue);
  }

  template <ValueType FieldFieldFieldValue>
  static constexpr FieldField make() {
    static_assert(isValueValid(FieldFieldFieldValue));
    return FieldField(FieldFieldType::template make<FieldFieldFieldValue>());
  }

  static FieldField UNSAFE_make(const FieldFieldType FieldFieldField) {
    return FieldField(FieldFieldField);
  }
};

} // namespace tiva

#endif // TIVA_FIELD_FIELDFIELD_H
