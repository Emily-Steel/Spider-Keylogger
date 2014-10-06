# - Try to find the boost threadpool library
# Will define:
#
# BOOSTTHREADPOOL_INCLUDE_DIRS - include directories needed to use the library
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

FIND_PATH(BOOSTTHREADPOOL_INCLUDE_DIRS
          NAMES threadpool.hpp
          PATH_SUFFIXES boost)
             
# post-process inlude path
IF(BOOSTTHREADPOOL_INCLUDE_DIRS)
    STRING(REGEX REPLACE boost$$ "" BOOSTTHREADPOOL_INCLUDE_DIRS ${BOOSTTHREADPOOL_INCLUDE_DIRS})
    SET(BOOSTTHREADPOOL_INCLUDE_DIRS ${BOOSTTHREADPOOL_INCLUDE_DIRS} CACHE PATH "Boost threadpool include dirs" FORCE)
ENDIF()

FIND_PACKAGE_HANDLE_STANDARD_ARGS(BoostThreadpool DEFAULT_MSG BOOSTTHREADPOOL_INCLUDE_DIRS)

# only visible in advanced view
MARK_AS_ADVANCED(BOOSTTHREADPOOL_INCLUDE_DIRS)
