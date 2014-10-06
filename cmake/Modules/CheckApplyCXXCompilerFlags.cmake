#
# This only works if included after the line containing the PROJECT call in
# CMake.
#
# COMPILER_CXX_FLAGS(FLAGS)
#
# Copyright (C) 2011 by Hugues
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

INCLUDE(CheckCXXCompilerFlag)
INCLUDE(ParseArguments)

FUNCTION(COMPILER_CXX_FLAGS)
	PARSE_ARGUMENTS(ARG "FLAGS" "" ${ARGN})
	FOREACH(F ${ARG_FLAGS})
	  #we make a good unique variable name for the check
	  STRING(REGEX REPLACE "[-+=]" "_" F_CHECK_NAME ${F})
	  SET(F_CHECK_NAME CHECK_CXX_FLAG${F_CHECK_NAME})
	  #now we do the check
	  CHECK_CXX_COMPILER_FLAG(${F} ${F_CHECK_NAME})
	  #if the check pass, lets add the definition
	  IF(${F_CHECK_NAME})
		ADD_DEFINITIONS(${F})
	  ENDIF(${F_CHECK_NAME})
	ENDFOREACH(F ${ARG_FLAGS})
ENDFUNCTION()
