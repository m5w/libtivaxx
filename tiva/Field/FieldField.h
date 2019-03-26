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

template <class FieldFieldFieldType, class FieldFieldIsValueValid>
class FieldField : public BaseField<typename FieldFieldFieldType::ValueType> {
public:
  using ValueType = typename FieldFieldFieldType::ValueType;

private:
  using BaseFieldType = BaseField<ValueType>;

  constexpr explicit FieldField(const FieldFieldFieldType FieldFieldField)
      : BaseFieldType(FieldFieldField) {}

public:
  static constexpr auto getMask() { return FieldFieldFieldType::getMask(); }

  static constexpr bool isValueValid(const ValueType FieldFieldFieldValue) {
    constexpr FieldFieldIsValueValid IsValueValid;
    return FieldFieldFieldType::isValueValid(FieldFieldFieldValue) &&
           IsValueValid(FieldFieldFieldValue);
  }

  template <ValueType FieldFieldFieldValue>
  static constexpr FieldField make() {
    static_assert(isValueValid(FieldFieldFieldValue));
    return FieldField(
        FieldFieldFieldType::template make<FieldFieldFieldValue>());
  }

  static FieldField UNSAFE_make(const FieldFieldFieldType FieldFieldField) {
    return FieldField(FieldFieldField);
  }
};

} // namespace tiva

#endif // TIVA_FIELD_FIELDFIELD_H
