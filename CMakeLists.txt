# Copyright (c) 2021 Ojas Anand.
#
# This file is part of xdimav. xdimav is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version. GNU package is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of
# the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.


cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

project ("xdimav")

# Include sub-projects.
add_subdirectory ("src")
