# - Try to find the Intel Threading Building Blocks library
# Will define:
#
# TBB_INCLUDE_DIRS - include directories needed to use the C++ driver
# TBB_LIBRARIES - Libraries to link agains fpr the driver
# TBB_LIBRARY_DIRS - Directories containing the libraries (win)
# TBB_VERSION - Version of the TBB library that was found
# TBB_RUNTIME_LIBRARIES - Runtime libraries if found (dll on windows)
# TBB_RUNTIME_LIBRARY_DIRS - Directories containing runtime libraries
#
# Possible hints:
# TBB_ROOT - root directory of the TBB installation
# TBB_DEBUG - if true, use the debug libraries of tbb instead of stripped ones
# TBB_BITS - value of 32 or 64 indicating the os type, default 32
# TBB_LIB_PATH - path containing the libraries to use
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

GET_FILENAME_COMPONENT(FIND_TBB_MODULE_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PATH(TBB_INCLUDE_DIRS
          HINTS ${TBB_ROOT}/include
                ${CMAKE_INSTALL_PREFIX}/include
          NAMES tbb.h
          PATH_SUFFIXES tbb)

IF(TBB_DEBUG)
    MESSAGE(STATUS "TBB debug version requested (TBB_DEBUG: ${TBB_DEBUG})")
    SET(TBB_LIB_NAME "tbb_debug")
    SET(TBBMALLOC_LIB_NAME "tbbmalloc_debug")
ELSE()
    MESSAGE(STATUS "TBB normal version requested (TBB_DEBUG: ${TBB_DEBUG})")
    SET(TBB_LIB_NAME "tbb")
    SET(TBBMALLOC_LIB_NAME "tbbmalloc")
ENDIF()

SET(TBB_LIBRARIES "")

SET(TBB_BITS "32")
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
	SET(TBB_BITS "64")
ENDIF()

SET(TBB_FOLDER_SUFFIX release)
SET(TBB_VC_FOLDER Release)
IF(TBB_DEBUG)
	SET(TBB_FOLDER_SUFFIX debug)
	SET(TBB_VC_FOLDER Debug)
ENDIF()
SET(TBB_LIBRARY_HINTS ${TBB_ROOT}/lib
                      ${TBB_ROOT}
                      ${TBB_LIB_PATH}
					  "${TBB_ROOT}/lib/ia${TBB_BITS}/vc8"
                      "${TBB_ROOT}/lib/ia${TBB_BITS}/vc9"
					  "${TBB_ROOT}/lib/ia${TBB_BITS}/vc10"
					  "${TBB_ROOT}/build/windows_ia${TBB_BITS}_cl_vc8_${TBB_FOLDER_SUFFIX}"
                      "${TBB_ROOT}/build/windows_ia${TBB_BITS}_cl_vc9_${TBB_FOLDER_SUFFIX}"
					  "${TBB_ROOT}/build/windows_ia${TBB_BITS}_cl_vc10_${TBB_FOLDER_SUFFIX}"
					  "${TBB_ROOT}/build/vsproject/ia${TBB_BITS}/${TBB_VC_FOLDER}"
                      ${CMAKE_INSTALL_PREFIX}
                      ${CMAKE_INSTALL_PREFIX}/lib)

FIND_LIBRARY(TBB_LIBRARY
             HINTS ${TBB_LIBRARY_HINTS}
             NAMES ${TBB_LIB_NAME})
FIND_LIBRARY(TBBMALLOC_LIBRARY
             HINTS ${TBB_LIBRARY_HINTS}
             NAMES ${TBBMALLOC_LIB_NAME})
			 
IF(TBB_LIBRARY AND TBBMALLOC_LIBRARY)
    SET(TBB_LIBRARIES ${TBB_LIBRARY} ${TBBMALLOC_LIBRARY})
ENDIF()

IF(WIN32)
    FIND_FILE(TBB_RUNTIME_LIBRARY
              HINTS ${TBB_LIBRARY_HINTS}
              NAMES "${TBB_LIB_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    FIND_FILE(TBBMALLOC_RUNTIME_LIBRARY
              HINTS ${TBB_LIBRARY_HINTS}
              NAMES "${TBBMALLOC_LIB_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    IF(TBB_RUNTIME_LIBRARY)
        LIST(APPEND TBB_RUNTIME_LIBRARIES ${TBB_RUNTIME_LIBRARY})
    ENDIF()
    IF(TBBMALLOC_RUNTIME_LIBRARY)
        LIST(APPEND TBB_RUNTIME_LIBRARIES ${TBBMALLOC_RUNTIME_LIBRARY})
    ENDIF()
ELSE()
    SET(TBB_RUNTIME_LIBRARIES ${TBB_LIBRARIES})
ENDIF()

IF(TBB_RUNTIME_LIBRARIES)
    FOREACH(LIB ${TBB_RUNTIME_LIBRARIES})
        GET_FILENAME_COMPONENT(LIB_DIR ${LIB} PATH)
        LIST(APPEND TBB_RUNTIME_LIBRARY_DIRS ${LIB_DIR})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES TBB_RUNTIME_LIBRARY_DIRS)
ENDIF()

# post-process inlude path
IF(TBB_INCLUDE_DIRS)
    STRING(REGEX REPLACE tbb/?$$ "" TBB_INCLUDE_DIRS ${TBB_INCLUDE_DIRS})
ENDIF()
SET(TBB_INCLUDE_DIRS ${TBB_INCLUDE_DIRS} CACHE PATH "TBB include dirs" FORCE)

IF(NOT TBB_VERSION_ACCEPTABLE)

	# find out the TBB version that is present
	CONFIGURE_FILE("${FIND_TBB_MODULE_DIR}/ExtractTBBVersion.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/ExtractTBBVersion.cpp" @ONLY)
	TRY_RUN(TBB_VERSION_RUN_RESULT TBB_VERSION_COMPILE_RESULT
			"${CMAKE_BINARY_DIR}"
			"${CMAKE_CURRENT_BINARY_DIR}/ExtractTBBVersion.cpp"
			CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${TBB_LIBRARY}"
			RUN_OUTPUT_VARIABLE TBB_VERSION
			COMPILE_OUTPUT_VARIABLE TBB_VERSION_COMPILE_OUT)
	#MESSAGE("Version check compiled: ${TBB_VERSION_COMPILE_RESULT} - ${TBB_VERSION_COMPILE_OUT}")
	MESSAGE(STATUS "TBB_VERSION: ${TBB_VERSION}")

	# check if the version is acceptable
	SET(TBB_VERSION_ACCEPTABLE TRUE)
	IF(TBB_FIND_VERSION)
		
		MESSAGE(STATUS "TBB version check requested with target version ${TBB_FIND_VERSION}")
		
		IF(NOT TBB_VERSION_COMPILE_RESULT)
			# compiling did not work, no version extracted
			SET(TBB_VERSION_ACCEPTABLE FALSE)
		ELSEIF(NOT TBB_VERSION_RUN_RESULT EQUAL 0)
			# running did not work
			SET(TBB_VERSION_ACCEPTABLE FALSE)
		ELSEIF(${TBB_VERSION} VERSION_LESS ${TBB_FIND_VERSION})
			# wrong version
			SET(TBB_VERSION_ACCEPTABLE FALSE)
		ELSE()
		    # store we do not want to repeat this check...
			SET(TBB_VERSION_ACCEPTABLE TRUE CACHE BOOL "TBB version was checked and is sufficient" FORCE)
		ENDIF()
		
	ENDIF()

ENDIF()

FIND_PACKAGE_HANDLE_STANDARD_ARGS(TBB DEFAULT_MSG TBB_INCLUDE_DIRS TBB_LIBRARIES TBB_VERSION_ACCEPTABLE)

# only visible in advanced view
MARK_AS_ADVANCED(TBB_INCLUDE_DIRS TBB_LIBRARIES TBB_LIBRARY TBBMALLOC_LIBRARY TBB_VERSION_ACCEPTABLE)
