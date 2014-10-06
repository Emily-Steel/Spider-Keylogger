# - If the project is maintained in git, this macro extracts git version
# information using "git determine".
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

FIND_PROGRAM(GIT_EXECUTABLE "git")

FUNCTION(GIT_PROJECT_VERSION LATEST_TAG COMMIT_NUMBER COMMIT_ID RELEASE_BRANCH)

    SET(${LATEST_TAG} "" PARENT_SCOPE)
    SET(${COMMIT_NUMBER} "" PARENT_SCOPE)
    SET(${COMMIT_ID} "" PARENT_SCOPE)
    SET(${RELEASE_BRANCH} FALSE PARENT_SCOPE)

    IF(NOT GIT_EXECUTABLE)
        RETURN()
    ENDIF()
    
    # check whether this is a git repository by calling "git status" once
    EXECUTE_PROCESS(COMMAND ${GIT_EXECUTABLE} status
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    RESULT_VARIABLE STATUS_RESULT
                    OUTPUT_QUIET
                    ERROR_QUIET)
    IF(NOT STATUS_RESULT EQUAL 0)
        RETURN()
    ENDIF()
    
    MESSAGE(STATUS "This is a git repository")
    
    # first, define the last commit id using git log.
    # This is necessary, as git describe later might fail on shallow clones
    EXECUTE_PROCESS(COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:g%h
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    RESULT_VARIABLE HASH_RESULT
                    OUTPUT_VARIABLE HASH_OUTPUT)
    
    IF(NOT HASH_RESULT EQUAL 0)
        MESSAGE(STATUS "Unable to extract the git commit hash.")
        RETURN()
    ENDIF()
    
    STRING(STRIP ${HASH_OUTPUT} ID)    
    SET(${COMMIT_ID} ${ID} PARENT_SCOPE)
    
    # After the commit hash was extracted safely we can try to use the full
    # git describe logic, which is now safe to fail. 
    EXECUTE_PROCESS(COMMAND ${GIT_EXECUTABLE} describe --tags --match release-*.* --long
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    RESULT_VARIABLE VERSION_RESULT
                    OUTPUT_VARIABLE VERSION_OUTPUT)
           
    # we should not fail if git execution had an error         
    IF(NOT VERSION_RESULT EQUAL 0)
        RETURN()
    ENDIF()

    # make the matching against the branch more specific and grab the respective
    # information
    STRING(STRIP ${VERSION_OUTPUT} VERSION_OUTPUT)
    STRING(REGEX REPLACE "(release-[0-9]+\\.[0-9]+)-([0-9]+)-(.+)" "\\1;\\2;\\3" VERSION_MATCH ${VERSION_OUTPUT})

    LIST(LENGTH VERSION_MATCH MATCH_LENGTH)
    IF(NOT MATCH_LENGTH EQUAL 3)
        MESSAGE(WARNING "Could not extract patch version from git describe call")
        RETURN()
    ENDIF()

    LIST(GET VERSION_MATCH 0 TAG)
    LIST(GET VERSION_MATCH 1 NUMBER)

    # ensure that we are currently on a release branch
    EXECUTE_PROCESS(COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    RESULT_VARIABLE BRANCH_RESULT
                    OUTPUT_VARIABLE BRANCH_OUTPUT)

    IF(NOT BRANCH_RESULT EQUAL 0)
        MESSAGE(WARNING "Skiping the definition of the project version from git because the current branch could not be determined.")
        RETURN()
    ENDIF()
    STRING(STRIP "${BRANCH_OUTPUT}" BRANCH_OUTPUT)
    STRING(REGEX MATCH "^[0-9]+\\.[0-9]+$" BRANCH_MATCH ${BRANCH_OUTPUT})

    IF("" STREQUAL BRANCH_MATCH)
        MESSAGE(STATUS "This repository is on a non-release branch. Not defining patch version.")
        SET(${COMMIT_NUMBER} 0 PARENT_SCOPE)
        SET(${RELEASE_BRANCH} FALSE PARENT_SCOPE)
    ELSE()
        SET(${COMMIT_NUMBER} ${NUMBER} PARENT_SCOPE)
        SET(${RELEASE_BRANCH} TRUE PARENT_SCOPE)
    ENDIF()

    SET(${LATEST_TAG} ${TAG} PARENT_SCOPE)

ENDFUNCTION()
