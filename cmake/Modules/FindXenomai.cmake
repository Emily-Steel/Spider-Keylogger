# - Try to find the Xenomai Real-Time 
# Will define:
#
# XENOMAI_INCLUDE_DIR - Include directories needed to use the C++ driver
# XENOMAI_INCLUDE_POSIX_DIR - Include directories for POSIX systems
# XENOMAI_POSIX_WRAPPERS - Directories containing the libraries (win)
# XENOMAI_LIBRARY_XENOMAI - Xenomai library 
# XENOMAI_LIBRARY_NATIVE - Native library
# XENOMAI_LIBRARY_PTHREAD_RT - 
# XENOMAI_LIBRARY_RTDM - 
# XENOMAI_DEFINITIONS - Xenomai definitions / compiler flags
#
# Possible hints:
# XENOMAI_ROOT - root directory of the TBB installation
#
# Copyright (C) 2010 by Arne Nordmann <anordman at cor-lab dot de>
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

	# Search Path
	SET(XENOMAI_SEARCH_PATH /usr/include/xenomai /usr/local/xenomai /usr/xenomai /usr)
	
	# Try to find xeno-config.h
	FIND_PATH(XENOMAI_DIR xeno_config.h ${XENOMAI_SEARCH_PATH})

	IF(XENOMAI_DIR)
	
		SET(XENOMAI_FOUND TRUE)

		# Set include directory
		IF(XENOMAI_DIR STREQUAL "/usr/include/xenomai")
			# We are on ubuntu
			SET(XENOMAI_INCLUDE_DIR ${XENOMAI_DIR})
			SET(XENOMAI_INCLUDE_POSIX_DIR ${XENOMAI_DIR}/posix)
		ELSE(XENOMAI_DIR STREQUAL "/usr/include/xenomai")
			SET(XENOMAI_INCLUDE_DIR ${XENOMAI_DIR}/include)
			SET(XENOMAI_INCLUDE_POSIX_DIR ${XENOMAI_DIR}/include/posix)
		ENDIF(XENOMAI_DIR STREQUAL "/usr/include/xenomai")

		# Find xenomai pthread
		FIND_LIBRARY(XENOMAI_LIBRARY_NATIVE native ${XENOMAI_DIR}/lib)
		FIND_LIBRARY(XENOMAI_LIBRARY_XENOMAI xenomai ${XENOMAI_DIR}/lib)
		FIND_LIBRARY(XENOMAI_LIBRARY_PTHREAD_RT pthread_rt rtdm ${XENOMAI_DIR}/lib)
		FIND_LIBRARY(XENOMAI_LIBRARY_RTDM rtdm ${XENOMAI_DIR}/lib)

		# Find posix wrappers
		FIND_FILE(XENOMAI_POSIX_WRAPPERS lib/posix.wrappers ${XENOMAI_SEARCH_PATH})

		# Add compile/preprocess options
		SET(XENOMAI_DEFINITIONS "-D_GNU_SOURCE -D_REENTRANT -Wall -pipe -D__XENO__")
	
	ENDIF(XENOMAI_DIR)

ENDIF(UNIX)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Xenomai DEFAULT_MSG XENOMAI_DIR)
