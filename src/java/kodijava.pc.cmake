prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}/lib@LIB_SUFFIX@
includedir=${prefix}/include

Name: kodidevkit
Description: Library who bring java interface between a addon and Kodi
Version: @kodidevkit_VERSION_STRING@

Libs: -L${libdir} -lkodijava
Cflags: -I${includedir}
