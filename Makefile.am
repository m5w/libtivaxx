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

libtiva___a_SOURCES = \
	tiva/SystemControl/GpioPort.cpp \
	tiva/SystemControl/Registers.cpp

libtiva___a_includedir = $(includedir)

nobase_libtiva___a_include_HEADERS = \
	tiva/Field/BaseField.h \
	tiva/Field/DerivedField.h \
	tiva/Field/EnumeratedField.h \
	tiva/Field/Field.h \
	tiva/Field/FieldIsValueValid.h \
	tiva/Field/FieldSize.h \
	tiva/Field/UNSAFE_Field.h \
	tiva/Register/BaseRegisterField.h \
	tiva/Register/MemorymappedRegister.h \
	tiva/Register/ReadRegisterField.h \
	tiva/Register/ReadableMemorymappedRegister.h \
	tiva/Register/Register.h \
	tiva/Register/RegisterBitNumber.h \
	tiva/Register/RegisterField.h \
	tiva/Register/RoMemorymappedRegister.h \
	tiva/Register/RwMemorymappedRegister.h \
	tiva/Register/UNSAFE_RegisterField.h \
	tiva/Register/WoMemorymappedRegister.h \
	tiva/Register/WriteableMemorymappedRegister.h \
	tiva/SystemControl/GpioPort.h \
	tiva/SystemControl/Registers.h \
	tiva/SystemControl/RunModeClockGatingControlField.h \
	tiva/Type/BaseIntervalNumber.h \
	tiva/Type/LclosedIntervalNumber.h \
	tiva/Type/getLsignificantBits.h \
	tiva/Type/getMsignificantBits.h

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
