# - Try to find qt-labs scxml binary 
# Will define:
#
# SCC_FOUND - If qt-labs scxml was found
# SCC_EXECUTABLE - SCC binary path
#
# Possible hints:
# SCC_ROOT - root directory of the SCC innstallation
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

    # Try to find scc binary
    FIND_PROGRAM(SCC_EXECUTABLE
              NAME scc
              HINTS "${SCC_ROOT}"
                    "${SCC_ROOT}/bin"
                    "${CMAKE_INSTALL_PREFIX}"
                    "${CMAKE_INSTALL_PREFIX}/bin")

ENDIF(UNIX)

MACRO(SCC_GENERATE_HEADER SCXML)
    SET(SC_HEADER "${SCXML}.h")
    ADD_CUSTOM_COMMAND(
        OUTPUT ${SC_HEADER}
        COMMAND ${SCC_EXECUTABLE}
        ARGS "-i" ${SCXML} "-o" ${SC_HEADER}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating ${SC_HEADER}")
ENDMACRO()

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SCC DEFAULT_MSG SCC_FOUND SCC_EXECUTABLE)
