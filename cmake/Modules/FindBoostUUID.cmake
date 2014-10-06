# -*- mode: cmake -*-

# - Try to find the boost uuid library
# Will define:
#
# BOOSTUUID_INCLUDE_DIRS - include directories needed to use the library
#
# Uses:
#
# BOOSTUUID_ROOT - hint for the installation root of boost uuid
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

INCLUDE(FindPackageHandleStandardArgs)

# we use a result of FindBoost as a hint for searching the uuid paths
IF(NOT Boost_FOUND)
    FIND_PACKAGE(Boost)
ENDIF()
FIND_PATH(BOOSTUUID_INCLUDE_DIRS
          NAMES boost/uuid/uuid.hpp
          HINTS ${BOOSTUUID_ROOT} ${BOOST_ROOT} ${CMAKE_INSTALL_PREFIX} ${Boost_INCLUDE_DIRS}
          PATH_SUFFIXES include)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(BoostUUID DEFAULT_MSG BOOSTUUID_INCLUDE_DIRS)

# only visible in advanced view
MARK_AS_ADVANCED(BOOSTUUID_INCLUDE_DIRS)
