{
    'includes': ['common.gypi'],
    'make_global_settings': [
        ['CXX','/usr/bin/clang++'],
        ['LINK','/usr/bin/clang++'],
    ],
    'variables': { 
        'src_files': '<!(python enum_src_files.py ../source)',
        'test_files': '<!(python enum_src_files.py ../test)',
        },
    'target_defaults': {
        'include_dirs': [
            '../third_party/opengl',
            '../third_party/glew/include',
            '../third_party/eigen/Eigen',
            '../third_party/spdlog/include',
        ],
        'msvs_settings': {
            'VCCLCompilerTool': {
                'WarningLevel': '4', # /W4
            },
            'VCLinkerTool': {
                'AdditionalDependencies': [
                    'kernel32.lib',
                    'user32.lib',
                    'gdi32.lib',
                    'winspool.lib',
                    'comdlg32.lib',
                    'advapi32.lib',
                    'shell32.lib',
                    'ole32.lib',
                    'oleaut32.lib',
                    'uuid.lib',
                    'odbc32.lib',
                    'odbccp32.lib',
                    'opengl32.lib',
                ],
                # 'TargetMachine': '17'
            },
            'VCLibrarianTool': {
                # 'TargetMachine': '17'
            },
        },
        'xcode_settings': {
            'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
            'CLANG_CXX_LANGUAGE_STANDARD': 'c++0x',
            'MACOSX_DEPLOYMENT_TARGET': '10.8',
                'CLANG_CXX_LIBRARY': 'libc++',
        },
    },
    'targets': [
    {
        'target_name': 'tempura_engine',
        'product_name': 'tempura_engine',
        'type': 'static_library',
        'include_dirs': [
            '../source',
        ],
        'sources': [
            '<@(src_files)',
            ],
        'xcode_settings': {
            'GCC_INLINES_ARE_PRIVATE_EXTERN': 'YES',
                'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES',
        },
        'conditions': [
            ['OS=="mac"', {
                'sources!': [
                    '../source/system/windows/window.cpp',
                    '../source/system/windows/application.cpp',
                    ]}],
            ['OS=="win"', {
                'sources!': [
                    '../source/system/mac/window.mm',
                    '../source/system/mac/application.mm',
                    ]}],
        ],
    },
    {
        'target_name': 'tempura_test',
        'product_name': 'tempura_test',
        'type': 'executable',
        'dependencies': [
            'tempura_engine',
        ],
        'include_dirs': [
            '../source',
        ],
        'sources': [
            '<@(test_files)',
        ],
        'xcode_settings': {
            'GCC_INLINES_ARE_PRIVATE_EXTERN': 'YES',
                'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES',
        },
        'conditions': [
            ['OS=="mac"', {
                'libraries': [
                    '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework',
                    '$(SDKROOT)/System/Library/Frameworks/OpenGL.framework',
                    '/usr/local/lib/libGLEW.dylib',
                    ]}],
            ['OS=="win"', {
                'libraries': [
                    #'../third_party/glew/lib/Release/x64/glew32.lib',
                    'd3d11.lib',
                    'dxgi.lib',
                    ]}],
        ],
    },
    ]# targets
}

