# -*- coding: utf-8 -*-
import sys
import gyp

import create_opengl_link_file

def gen_proj():
    gyp.main(['tempura.gyp', '--depth=.', '--generator-output=./project_files'])

if __name__ == '__main__':
    #create_opengl_link_file.download_extension_files()
    #create_opengl_link_file.create_opengl_link_file()
    sys.exit(gen_proj())
