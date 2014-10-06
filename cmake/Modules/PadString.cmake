# - Pads a string on the left side to reach a specified length
# This function pads a string on the left side with a specified character to
# reach the specified length. If the string length is already long enough or
# longer, the string will not be modified.
#
# PAD_STRING(OUT_VARIABLE DESIRED_LENGTH FILL_CHAR VALUE)
#
#     OUT_VARIABLE: name of the resulting variable to create
#     DESIRED_LENGTH: desired length of the generated string
#     FILL_CHAR: character to use for padding
#     VALUE: string to pad
#
# Copyright (C) 2011 by Johannes Wienke <jwienke at techfak dot uni-bielefeld dot de>
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

FUNCTION(PAD_STRING OUT_VARIABLE DESIRED_LENGTH FILL_CHAR VALUE)
    STRING(LENGTH "${VALUE}" VALUE_LENGTH)
    MATH(EXPR REQUIRED_PADS "${DESIRED_LENGTH} - ${VALUE_LENGTH}")
    SET(PAD ${VALUE})
    IF(REQUIRED_PADS GREATER 0)
        MATH(EXPR REQUIRED_MINUS_ONE "${REQUIRED_PADS} - 1")
        FOREACH(FOO RANGE ${REQUIRED_MINUS_ONE})
            SET(PAD "${FILL_CHAR}${PAD}")
        ENDFOREACH()
    ENDIF()
    SET(${OUT_VARIABLE} "${PAD}" PARENT_SCOPE)
ENDFUNCTION()
