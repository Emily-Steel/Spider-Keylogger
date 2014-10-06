# - Find JSONCpp
#
# This module defines
#  JSONCPP_INCLUDE_DIR, where to find json.h, etc.
#  JSONCPP_LIBRARIES, the libraries needed to use jsoncpp.
#
# Copyright (C) 2010 by Johannes Wienke <jwienke at techfak dot uni-bielefeld dot de>
#
# This file may be licensed under the terms of the
# GNU Lesser General Public License Version 3 (the ``LGPL''),
# or (at your option) any later version.
#
# Software distributed under the License is distributed
# on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
# express or implied. See the LGPL for the specific language
# governing rights and limitations.
#
# You should have received a copy of the LGPL along with this
# program. If not, go to http://www.gnu.org/licenses/lgpl.html
# or write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# The development of this software was supported by:
#   CoR-Lab, Research Institute for Cognition and Robotics
#     Bielefeld University
#
# adapted from http://code.google.com/p/emeraldviewer/

FIND_PATH(JSONCPP_INCLUDE_DIR
          NAMES json.h
          PATHS "/usr/local/include" "/usr/include"
          PATH_SUFFIXES jsoncpp json)

# post-process inlude path
IF(JSONCPP_INCLUDE_DIR)
    STRING(REGEX REPLACE "/json.*$$" "" JSONCPP_INCLUDE_DIR ${JSONCPP_INCLUDE_DIR})
    SET(JSONCPP_INCLUDE_DIR ${JSONCPP_INCLUDE_DIR} CACHE PATH "JsonCpp include dir" FORCE)
ENDIF()

# get the GCC compiler version
EXEC_PROGRAM(${CMAKE_CXX_COMPILER}
             ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion
             OUTPUT_VARIABLE _gcc_COMPILER_VERSION
             OUTPUT_STRIP_TRAILING_WHITESPACE)

SET(JSONCPP_NAMES ${JSONCPP_NAMES} libjson_linux-gcc-${_gcc_COMPILER_VERSION}_libmt.so)
FIND_LIBRARY(JSONCPP_LIBRARIES
             NAMES ${JSONCPP_NAMES})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(JsonCpp DEFAULT_MSG JSONCPP_LIBRARIES JSONCPP_INCLUDE_DIR)

MARK_AS_ADVANCED(JSONCPP_LIBRARIES JSONCPP_INCLUDE_DIR)
