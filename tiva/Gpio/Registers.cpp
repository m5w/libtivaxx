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

#include "tiva/Gpio/Registers.h"

namespace tiva {

namespace detail {

Register<RwMemorymappedRegister<std::uint32_t>, 0x0000'0000,
         Pin7AlternateFunctionSelectField, Pin6AlternateFunctionSelectField,
         Pin5AlternateFunctionSelectField, Pin4AlternateFunctionSelectField,
         Pin3AlternateFunctionSelectField, Pin2AlternateFunctionSelectField,
         Pin1AlternateFunctionSelectField, Pin0AlternateFunctionSelectField>
    GpioPortBGpioafsel(RwMemorymappedRegister<std::uint32_t>(0x4005'9000 +
                                                             0x420));
Register<RwMemorymappedRegister<std::uint32_t>, 0x0000'0000,
         RegisterField<Pb7PortMuxControlField::FieldType, 28>,
         RegisterField<Pb6PortMuxControlField::FieldType, 24>,
         RegisterField<Pb5PortMuxControlField::FieldType, 20>,
         RegisterField<Pb4PortMuxControlField::FieldType, 16>,
         RegisterField<Pb3PortMuxControlField::FieldType, 12>,
         RegisterField<Pb2PortMuxControlField::FieldType, 8>,
         RegisterField<Pb1PortMuxControlField::FieldType, 4>,
         RegisterField<Pb0PortMuxControlField::FieldType, 0>>
    GpioPortBGpiopctl(RwMemorymappedRegister<std::uint32_t>(0x4005'9000 +
                                                            0x52C));

} // namespace detail

} // namespace tiva
