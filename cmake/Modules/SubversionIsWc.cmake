# - Checks whether a folder is a subversion wokring copy
# The existing subversion wrappers in cmake do not provide a way to check
# whether a folder really is a working copy of subversion. This module adds
# a function to check this.
#
# Subversion_IS_WC(FOLDER RESULT_VAR)
#   Checks if FOLDER is a SVN working copy and sets the RESULT_VAR to a bool
#   value.
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

FIND_PACKAGE(Subversion)

FUNCTION(Subversion_IS_WC FOLDER RESULT_VAR)

    IF(Subversion_FOUND)
    
        # SVN info does not like .. as paths, so be sure that we use a full path
        GET_FILENAME_COMPONENT(ABS_FOLDER ${FOLDER} ABSOLUTE)
        EXECUTE_PROCESS(COMMAND ${Subversion_SVN_EXECUTABLE} info ${ABS_FOLDER}
                        RESULT_VARIABLE INFO_RESULT
                        OUTPUT_VARIABLE IGNORED
                        ERROR_VARIABLE IGNORED)
        IF(INFO_RESULT EQUAL 0)
            SET(${RESULT_VAR} TRUE PARENT_SCOPE)
        ELSE()
            SET(${RESULT_VAR} FALSE PARENT_SCOPE)
        ENDIF()
    
    ELSE()
        MESSAGE(STATUS "Cannot check whether folder ${FOLDER} is a svn working copy because svn was not found. Returning FALSE.")
        SET(${RESULT_VAR} FALSE PARENT_SCOPE)
    ENDIF()

ENDFUNCTION()
