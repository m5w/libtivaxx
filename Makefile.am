# Copyright (C) 2019 Matthew Marting
#
# This file is part of libtiva++.
#
# libtiva++ is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libtiva++ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with libtiva++.  If not, see <https://www.gnu.org/licenses/>.

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libtiva++.pc

aclocaldir = $(datadir)/aclocal

aclocal_DATA = \
	libtiva++.m4

lib_LIBRARIES = \
	libtiva++.a

libtiva___a_SOURCES =

libtiva___a_includedir = $(includedir)

nobase_libtiva___a_include_HEADERS = \
	tiva/Type/LclosedIntervalNumber.h \
	tiva/Type/BaseIntervalNumber.h \
	tiva/Type/getMsignificantBits.h \
	tiva/Type/getLsignificantBits.h \
	tiva/Field/DerivedField.h \
	tiva/Field/FieldIsValueValid.h \
	tiva/Field/BaseField.h \
	tiva/Field/EnumeratedField.h \
	tiva/Field/FieldSize.h \
	tiva/Field/Field.h \
	tiva/Field/UNSAFE_Field.h \
	tiva/Register/Register.h \
	tiva/Register/UNSAFE_RegisterField.h \
	tiva/Register/RwMemorymappedRegister.h \
	tiva/Register/ReadableMemorymappedRegister.h \
	tiva/Register/MemorymappedRegister.h \
	tiva/Register/WriteableMemorymappedRegister.h \
	tiva/Register/WoMemorymappedRegister.h \
	tiva/Register/RegisterField.h \
	tiva/Register/RoMemorymappedRegister.h \
	tiva/Register/ReadRegisterField.h \
	tiva/Register/BaseRegisterField.h \
	tiva/Register/RegisterBitNumber.h \
	tiva/SystemControl/GpioPortRcgcFieldType.h \
	tiva/SystemControl/GpioPortRcgcFieldLsignificantRegisterBitNumber.h \
	tiva/SystemControl/GpioPortIdentifier.h \
	tiva/SystemControl/RcgcField.h \
	tiva/Gpio/GpioPinAfselFieldType.h \
	tiva/Gpio/AfselField.h \
	tiva/Gpio/DenField.h \
	tiva/Gpio/GpioPinIdentifier.h \
	tiva/Gpio/GpioPinPmcFieldType.h \
	tiva/Gpio/GpioPinAfselFieldLsignificantRegisterBitNumber.h \
	tiva/Gpio/GpioPinOdeFieldType.h \
	tiva/Gpio/GpioPinPmcFieldLsignificantRegisterBitNumber.h \
	tiva/Gpio/PmcField.h \
	tiva/Gpio/GpioPort.h \
	tiva/Gpio/GpioPinGpioPortIdentifier.h \
	tiva/Gpio/OdeField.h \
	tiva/Gpio/GpioPinDenFieldType.h \
	tiva/Gpio/GpioPinDenFieldLsignificantRegisterBitNumber.h \
	tiva/Gpio/GpioPinOdeFieldLsignificantRegisterBitNumber.h

noinst_PROGRAMS = \
	libtiva++-test-Register.axf

.PHONY: test/Register/flash
test/Register/flash: libtiva++-test-Register.axf
	$(FLASH) $<

libtiva___test_Register_axf_SOURCES = \
	test/Register/main.cpp \
	test/Register/abort.cpp

libtiva___test_Register_axf_LDADD = \
	libtiva++.a

include $(includedir)/tivasdk.mk
include $(includedir)/uniflash.mk
