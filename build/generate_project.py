# -*- coding: utf-8 -*-
import sys
import platform
try:
  import gyp
except ImportError, e:
  import os.path
  sys.path.append(os.path.join(os.path.dirname(sys.argv[0]), 'pylib'))
  import gyp

import create_opengl_link_file

def gen_proj():
    if platform.system() == 'Windows':
        gyp.main(['tempura.gyp', '--depth=.', '--generator-output=./project_files', '-f', 'msvs', '-G', 'msvs_version=2012'])
    else:
        gyp.main(['tempura.gyp', '--depth=.', '--generator-output=./project_files'])

if __name__ == '__main__':
    #create_opengl_link_file.download_extension_files()
    #create_opengl_link_file.create_opengl_link_file()
    sys.exit(gen_proj())
