{
    'target_defaults': {
        'configurations': {
            'Debug': {
                'defines':['DEBUG'],
                'msvs_configuration_platform': 'x64',
                'msvs_target_platform': 'x64',
                'msbuild_settings': {
                    'ClCompile': {
                        'DebugInformationFormat': 'ProgramDatabase', # /Zi
                        'Optimization': 'Disabled',
                    },
                    'Link': {
                        'GenerateDebugInformation': 'true', # /DEBUG
                    },
                },
                'xcode_settings': {
                    'GCC_OPTIMIZATION_LEVEL': '0',
                    'CLANG_CXX_LANGUAGE_STANDARD': 'c++0x',
                    'MACOSX_DEPLOYMENT_TARGET': '10.8',
                },
            },
            'Release': {
                'msvs_configuration_platform': 'x64',
                'msvs_target_platform': 'x64',
            },
        },
        'default_configuration': 'Debug',
        #'default_configuration': 'Release',
    },
}
