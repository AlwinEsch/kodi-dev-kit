{
  'targets': [
    {
      'target_name': 'kodidevkit',
      'sources': [
        'src/kodi.cpp',

        'src/version.c',
        'src/kodidevkitjsJAVASCRIPT_wrap.cxx'
      ],
      'include_dirs': [
        'include',

      ],
      'variables': {
        "v8_version%": "<!(`command -v nodejs 2> /dev/null || echo node` -e 'console.log(process.versions.v8)' | sed 's/\.//g' | cut -c 1-5)",
        "arch%": "<!(`command -v nodejs 2> /dev/null || echo node` -e 'console.log(process.arch)')"
      },
      'cflags_cc!': [ '-fno-rtti', '-fno-exceptions' ],
      'cflags!': [ '-fno-exceptions' ],
      'conditions' : [
        ['OS=="android"', {
          'sources' : [ 'src/glob/glob.c' ],
          'include_dirs' : [ 'src/glob' ],
        }],
        [ 'arch=="x64" or arch=="ia32"', {
          'defines' : [ 'X86PLAT=ON' ],
        }],
        [ 'arch=="arm"', {
          'defines' : [ 'ARMPLAT=ON'],
        }],
      ],
      'defines' : [
        'SWIG',
        'SWIGJAVASCRIPT',
        'FIRMATA=ON',
        'ONEWIRE=ON',
        'BUILDING_NODE_EXTENSION=1',
        'SWIG_V8_VERSION=0x0<(v8_version)',
        'V8_VERSION=0x0<(v8_version)'
      ]
    }
  ]
}