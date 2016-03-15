# -*- coding: utf-8 -*-
import urllib

def create_opengl_extension():
    urllib.urlretrieve('http://www.opengl.org/registry/api/GL/glext.h', '../third_party/opengl/GL/glext.h')
    urllib.urlretrieve('http://www.opengl.org/registry/api/GL/glcorearb.h', '../third_party/opengl/GL/glcorearb.h')
    urllib.urlretrieve('http://www.opengl.org/registry/api/GL/glxext.h', '../third_party/opengl/GL/glxext.h')
    urllib.urlretrieve('http://www.opengl.org/registry/api/GL/wglext.h', '../third_party/opengl/GL/wglext.h')


if __name__ == '__main__':
    create_opengl_extension()
