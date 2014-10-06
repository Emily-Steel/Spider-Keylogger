# - A macro returning the current date.
#
# Copyright (C) 2012 by Johannes Wienke <jwienke at techfak dot uni-bielefeld dot de>
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

GET_FILENAME_COMPONENT(CURRENT_DATE_MODULE_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

FUNCTION(CURRENT_DATE RESULT)

    IF(UNIX)
        SET(CMD "date" "+%d/%m/%Y")
    ELSEIF(WIN32)
        FILE(TO_NATIVE_PATH ${CURRENT_DATE_MODULE_DIR} NATIVE_DIR)
        SET(CMD cmd /C "${NATIVE_DIR}/current_date.bat")
    ELSE()
        MESSAGE(STATUS "Current date cannot be parsed on this operating system.")
        SET(${RESULT} 000000 PARENT_SCOPE)
        RETURN()
    ENDIF()
    
    EXECUTE_PROCESS(COMMAND ${CMD}
                    OUTPUT_VARIABLE DATE_OUTPUT
                    RESULT_VARIABLE DATE_RESULT
                    ERROR_VARIABLE DATE_ERROR)

    IF(NOT DATE_RESULT EQUAL 0)
        MESSAGE(WARNING "error calling date command: ${DATE_RESULT} ${DATE_ERROR}")
        SET(${RESULT} 000000 PARENT_SCOPE)
        RETURN()
    ENDIF()

    SET(REPLACE "(..)/(..)/..(..).*" "\\3\\2\\1")       
    STRING(REGEX REPLACE ${REPLACE} DATE_STRING ${DATE_OUTPUT})
    SET(${RESULT} ${DATE_STRING} PARENT_SCOPE)
    
ENDFUNCTION()
