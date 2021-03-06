##########################################################################
# Simple ycm_extra_conf.py example                                       #
# Copyright (C) <2013>  Onur Aslan  <onur@onur.im>                       #
#                                                                        #
# This file is loaded by default. Place your own .ycm_extra_conf.py to   #
# project root to override this.                                         #
#                                                                        #
# This program is free software: you can redistribute it and/or modify   #
# it under the terms of the GNU General Public License as published by   #
# the Free Software Foundation, either version 3 of the License, or      #
# (at your option) any later version.                                    #
#                                                                        #
# This program is distributed in the hope that it will be useful,        #
# but WITHOUT ANY WARRANTY; without even the implied warranty of         #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          #
# GNU General Public License for more details.                           #
#                                                                        #
# You should have received a copy of the GNU General Public License      #
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  #
##########################################################################
# modifications                                                          #
# by Paul Seyfert <Paul.Seyfert@cern.ch>                                 #
##########################################################################

import os
import logging

logger = logging.getLogger('conf_logger')
logger.setLevel(logging.CRITICAL)
fh = logging.FileHandler('/tmp/ycmconflog.log')
logger.addHandler(fh)

thisdir = os.path.dirname(os.path.abspath(__file__))

# some default flags
# for more information install clang-3.2-doc package and
# check UsersManual.html
flags = [
    '-DHAVE_CONFIG_H',
    '-Wall',
    '-Werror',
    '-x',
    'c',
    '-DYCM_DIAGS=1',
    # for the zsh root dir
    # '-I' + os.path.join(thisdir, "Src"),
    # '-I' + os.path.join(thisdir, "Src/Zle"),
]

try:
    rootsys = os.environ['ROOTSYS']
    if os.path.isdir(os.path.join(rootsys, 'include')):
        flags += ['-I'+os.path.join(rootsys, 'include')]
except KeyError:
    pass

try:
    envflags = os.environ['CPPFLAGS'].split(' ')
    logger.info("envflags: {}".format(envflags))
    for envflag in envflags:
        logger.debug("checking: {}".format(envflag))
        if envflag.startswith("-I"):
            logger.debug("adding: {}".format(envflag))
            flags += [envflag]
except KeyError:
    pass


# youcompleteme is calling this function to get flags
# You can also set database for flags. Check: JSONCompilationDatabase.html in
# clang-3.2-doc package


def FlagsForFile(filename):
    return {
        'flags': flags,
        'do_cache': True
    }
