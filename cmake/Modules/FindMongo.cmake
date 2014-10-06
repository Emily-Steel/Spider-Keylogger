# - Try to find the C++ mongodb driver
# Will define:
#
# MONGO_INCLUDE_DIRS - include directories needed to use the C++ driver
# MONGO_LIBRARIES - Libraries to link agains fpr the driver
# MONGOD_EXECUTABLE - mongod server executable
#
# Possible hints:
# MONGO_ROOT - root directory of the mongodb installation
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

FIND_PATH(MONGO_INCLUDE_DIRS
          PATHS ${MONGO_ROOT}/include
          NAMES dbclient.h
          PATH_SUFFIXES mongo/client)

FIND_LIBRARY(MONGO_LIBRARIES
             PATHS ${MONGO_ROOT}/lib
             NAMES mongoclient)
             
# post-process inlude path
IF(MONGO_INCLUDE_DIRS)
    STRING(REPLACE mongo/client "" MONGO_INCLUDE_DIRS ${MONGO_INCLUDE_DIRS})
    SET(MONGO_INCLUDE_DIRS ${MONGO_INCLUDE_DIRS} CACHE PATH "MongoDB include dirs" FORCE)
ENDIF()

# find server executable
FIND_PROGRAM(MONGOD_EXECUTABLE mongod
             PATHS ${MONGO_ROOT}/bin)

# get the version
SET(MONGO_VERSION "0.0.0")
IF(MONGOD_EXECUTABLE)
    EXECUTE_PROCESS(COMMAND ${MONGOD_EXECUTABLE} --version OUTPUT_VARIABLE MONGOD_VERSION_OUT)
    STRING(REGEX MATCH "[0-9]\\.[0-9]\\.[0-9]" MONGO_VERSION "${MONGOD_VERSION_OUT}")
ENDIF()

# check version information
SET(MONGO_VERSION_ACCEPTABLE TRUE)
IF(Mongo_FIND_VERSION AND MONGO_VERSION)
    MESSAGE(STATUS "Mongo: requested version ${Mongo_FIND_VERSION}, found version ${MONGO_VERSION}")
    IF(${MONGO_VERSION} VERSION_LESS ${Mongo_FIND_VERSION})
        SET(MONGO_VERSION_ACCEPTABLE FALSE)
    ENDIF()
ENDIF()

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Mongo DEFAULT_MSG MONGO_INCLUDE_DIRS MONGO_LIBRARIES MONGOD_EXECUTABLE MONGO_VERSION MONGO_VERSION_ACCEPTABLE)

# only visible in advanced view
MARK_AS_ADVANCED(MONGO_INCLUDE_DIRS MONGO_LIBRARIES MONGOD_EXECUTABLE MONGO_VERSION)
