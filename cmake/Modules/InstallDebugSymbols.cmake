# - A utility function that install windows deubg symbols in case they exist.
#
# INSTALL_DEBUG_SYMBOLS(TARGETS target... [INSTALL_DIR dir])
#
# In case the project is built on windows in the correct configuration that
# prepares debug symbols, these symbols are installed by calling this function.
# Debug symbols are installed in the form of PDB files.
#
# Inputs:
#   TARGETS: the names of the CMake targets for which debug symbols should be
#            installed
#   INSTALL_DIR: directory to install the symbol files to. Relative paths are
#                interpreted relative to CMAKE_INSTALL_PREFIX. Defaults to bin.
#
# Targets need to be defined before calling this function.
#
# Copyright (C) 2014 by Johannes Wienke <jwienke at techfak dot uni-bielefeld dot de>
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

INCLUDE(GitProjectVersion)

FUNCTION(INSTALL_DEBUG_SYMBOLS)

    PARSE_ARGUMENTS(ARG "TARGETS;INSTALL_DIR" "" ${ARGN})

    SET(INSTALL_DIR bin)
    IF(ARG_INSTALL_DIR)
        SET(INSTALL_DIR "${ARG_INSTALL_DIR}")
    ENDIF()
    MESSAGE(STATUS "Installing debug symbols to '${INSTALL_DIR}'")

    STRING(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)

    IF(WIN32 AND (BUILD_TYPE STREQUAL "debug" OR BUILD_TYPE STREQUAL "relwithdebinfo"))

        FOREACH(TARGET ${ARG_TARGETS})

            ADD_CUSTOM_COMMAND(TARGET ${TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "$<TARGET_FILE_DIR:${TARGET}>/${TARGET}.pdb"
                    "${CMAKE_BINARY_DIR}/symbols/${TARGET}.pdb")
            INSTALL(FILES "${CMAKE_BINARY_DIR}/symbols/${TARGET}.pdb"
                    DESTINATION "${INSTALL_DIR}")
            MESSAGE(STATUS "Added install rule for pdb files to target ${TARGET}")

        ENDFOREACH()

        SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_BINARY_DIR}/symbols")

    ENDIF()

ENDFUNCTION()
