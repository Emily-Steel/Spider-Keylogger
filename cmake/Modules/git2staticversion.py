#!/usr/bin/env python
# ============================================================
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
#
# ============================================================

import os
import re
import subprocess
import sys

from distutils.spawn import find_executable

versionRegEx = re.compile('(?P<major>[0-9]+)\\.(?P<minor>[0-9]+)-(?P<patch>[0-9]+)-(?P<wcRevision>[a-zA-Z0-9]+)')

def run():
    
    # check arguments
    if len(sys.argv) != 2 or '-h' in sys.argv[1:] or '--help' in sys.argv[1:]:
        print("Usage: %s <project folder>" % sys.argv[0])
        print("Will write a vcsversion.cmake file to the specified project folder.")
        sys.exit(1)
    
    # find the git executable
    git = find_executable("git");
    if git is None:
        print("Unable to find the git executable. Add it to your PATH environment variable.")
        sys.exit(1)
        
    # find out the name of this branch
    branchProcess = subprocess.Popen([git, 'branch', '--no-color'], stdout=subprocess.PIPE, cwd=sys.argv[1])
    (branchOutput, branchError) = branchProcess.communicate()
    try:
        # python 3 support
        branchOutput = branchOutput.decode()
    except:
        pass
    if branchProcess.returncode != 0:
        print("Git failed: %s" % branchError)
        exit(1)
    branch = branchOutput.replace('*', '').strip()
    print("We're on branch: '%s'" % branch)
    
    # get the version from git
    versionProcess = subprocess.Popen([git, 'describe', '--tags', '--match', '*.*'], stdout=subprocess.PIPE, cwd=sys.argv[1])
    (versionOutput, versionError) = versionProcess.communicate()
    try:
        # python 3 support
        versionOutput = versionOutput.decode()
    except:
        pass
    if versionProcess.returncode != 0:
        print("Git failed: %s" % versionError)
        exit(1)
        
    # parse the version
    versionMatches = re.match(versionRegEx, versionOutput.strip())
    
    # write a file containing the information which can only be gathered from
    # the VCS
    versionFileContents = ""
    versionFileContents += 'SET(VCS_COMMIT_NUMBER_SINCE_BRANCH "%d")\n' % (int(versionMatches.groupdict()['patch']))
    versionFileContents += 'SET(VCS_COMMIT_ID "%s")\n' % (versionMatches.groupdict()['wcRevision'])

    print("will write:\n%s" % versionFileContents)

    with open(os.path.join(sys.argv[1], 'vcsversion.cmake'), 'w') as versionFile:
        versionFile.write(versionFileContents)

if __name__ == '__main__':
    run()
