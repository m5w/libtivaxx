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

AC_INIT([libtiva++], [0.2.3])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])
PKG_CHECK_MODULES([TIVASDK], [tivasdk])
AC_MSG_CHECKING([for [TIVASDK_INIT]])
m4_ifdef([TIVASDK_INIT],
[[]dnl
AC_MSG_RESULT([yes])[]dnl
],
[[]dnl
AC_MSG_RESULT([no])
AC_MSG_ERROR([[TIVASDK_INIT] not found])[]dnl
])
TIVASDK_INIT
TIVASDK_INIT_GCCARMNONEEABI
TIVASDK_INIT_SYSTEMINIT
TIVASDK_INIT_UNIFLASH
AC_CONFIG_FILES([Makefile libtiva++.pc])
AC_OUTPUT
