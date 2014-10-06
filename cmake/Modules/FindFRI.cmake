# - Try to find KUKA FRI (Fast Research Interface) 
# Will define:
#
# FRI_FOUND - If FRI was found
# FRI_DIR - FRI root dir (where headers were found)
# FRI_INCLUDE_DIRS - Include directories
#
# Possible hints:
# FRI_ROOT - root directory of the FRI innstallation
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
    
    # Try to find friComm.h
    FIND_PATH(FRI_DIR
              NAMES friComm.h
              HINTS "${FRI_ROOT}"
                    "${FRI_ROOT}/include"
                    "${CMAKE_INSTALL_PREFIX}/include"
              PATHS "${FRI_ROOT}"
                    "${FRI_ROOT}/include"
                    "${CMAKE_INSTALL_PREFIX}/include")
                    
    SET(FRI_INCLUDE_DIRS "${FRI_DIR}")

ENDIF(UNIX)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FRI DEFAULT_MSG FRI_FOUND FRI_DIR FRI_INCLUDE_DIRS)
