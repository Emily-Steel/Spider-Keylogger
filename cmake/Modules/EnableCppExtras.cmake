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

INCLUDE(CheckCXXCompilerFlag)

IF(UNIX)

    CHECK_CXX_COMPILER_FLAG(--std=c++1y CHECK_CXX_FLAG_StdCppExtra)
    IF(CHECK_CXX_FLAG_StdCppExtra)
        ADD_DEFINITIONS(--std=c++1y)
    ENDIF()

ELSEIF(MSVC)
# Nothing to do ?
ENDIF()