# -*- coding: utf-8 -*-
import urllib
import re

registry_url = 'http://www.opengl.org/registry/api/GL/'
opengl_dir = '../third_party/opengl/gl_ext/'
extension_files = ['glext.h', 'glcorearb.h', 'glxext.h', 'wglext.h']
temp_opengl_dir = '../source/temp/graphics/opengl/'

def download_extension_files():
    for file_name in extension_files:
        urllib.urlretrieve(registry_url + file_name, opengl_dir + file_name)

def create_opengl_link_file():
    # ファイルに応じたパターンを作成
    gl_pattern = re.compile(r'^GLAPI\s+\w+\s+APIENTRY\s+(\w+)\s+\(')
    glx_pattern = re.compile(r'^\w+\s+\**(glX\w+)\s+\(')
    wgl_pattern = re.compile(r'^\w+\s+WINAPI\s+(\w+)\s+\(')
    pattern_list = [gl_pattern, gl_pattern, glx_pattern, wgl_pattern]

    for (ext_file_name, pattern) in zip(extension_files, pattern_list):
        # リンクファイルを作成
        name = ext_file_name.split('.')[0]
        link_file_name = 'temp_' + name + '_link.inl'
        link_file = open(temp_opengl_dir + link_file_name, 'w')

        # 関数名を抜き出してリンクファイルに書き込み
        for line in open(opengl_dir + ext_file_name):
            match_object = pattern.match(line)
            if match_object is not None:
                function_name = match_object.group(1)
                l = 'TEMP_OPENGL_EXTENSION_LINK( PFN' + function_name.upper() + 'PROC, ' + function_name + ' )\n'
                link_file.write(l)

        link_file.close()

if __name__ == '__main__':
    download_extension_files()
    create_opengl_link_file()
