# - Execute a process and always return with status 0
#
# This is intended to be used in cmake script mode to execute a process and
# always return 0 even if the executed process failed. Use it like:
#   cmake -DCOMMAND="ls;-l;/tmp" -p IgnoreReturnCode.cmake
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

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(NOT COMMAND)
    MESSAGE(FATAL_ERROR "No command given with -DCOMMAND=\"command;one argument;another argument\"")
ENDIF()

MESSAGE(STATUS "Executing:")
FOREACH(COMMAND_PART ${COMMAND})
    MESSAGE(STATUS "  ${COMMAND_PART}")
ENDFOREACH()

EXECUTE_PROCESS(COMMAND ${COMMAND}
                RESULT_VARIABLE RETURN_CODE)
                
IF(RETURN_CODE STREQUAL "0")
    MESSAGE(STATUS "Command executed successfully: ${COMMAND}")
ELSE()
    MESSAGE(STATUS "Command execution was not successfull. Command ${COMMAND} returned exit code: ${RETURN_CODE}")
ENDIF()    
