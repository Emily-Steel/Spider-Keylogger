# - Try to find Open KUKA Control FRI 
# Will define:
#
# OPENKC_FOUND - If OpenKC was found
# OPENKC_DIR - OpenKC root dir (where headers were found)
# OPENKC_INCLUDE_DIRS - Include directories
# OPENKC_LIBRARIES - OpenKC library
#
# Possible hints:
# OPENKC_ROOT - root directory of the OpenKC innstallation
#
# Copyright (C) 2012 by Arne Nordmann <anordman at cor-lab dot de>
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

IF(UNIX)
    
    # Try to find xeno-config.h
    FIND_PATH(OPENKC_DIR
              NAMES fri_okc_comm.h
              HINTS "${OPENKC_ROOT}/include"
                    "${CMAKE_INSTALL_PREFIX}/include"
              PATHS "${OPENKC_ROOT}/include"
                    "${CMAKE_INSTALL_PREFIX}/include")

    IF(OPENKC_DIR)
    
        SET(OPENKC_FOUND TRUE)
        SET(OPENKC_INCLUDE_DIRS ${OPENKC_DIR})
        
        FIND_LIBRARY(OPENKC_LIBRARIES openkcfri
              HINTS "${OPENKC_DIR}/../lib"
                    "${OPENKC_ROOT}/lib"
                    "${CMAKE_INSTALL_PREFIX}/lib"
              PATHS "${OPENKC_DIR}/../lib"
                    "${OPENKC_ROOT}/lib"
                    "${CMAKE_INSTALL_PREFIX}/lib")

    ENDIF(OPENKC_DIR)

ENDIF(UNIX)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpenKC DEFAULT_MSG OPENKC_FOUND OPENKC_DIR OPENKC_LIBRARIES OPENKC_INCLUDE_DIRS)
