# vim:ft=config:

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

AC_DEFUN_ONCE([LIBTIVAXX_INIT],
[[]dnl
CPPFLAGS+=[]Join
"$LIBTIVAXX_CFLAGS"
LIBS+=[]Join
"$LIBTIVAXX_LIBS"[]dnl
])[]dnl
])# LIBTIVAXX_INIT
