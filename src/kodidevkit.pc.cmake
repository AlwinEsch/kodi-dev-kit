prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}/lib@LIB_SUFFIX@
includedir=${prefix}/include

Name: kodidevkit
Description: Library who bring interface between a addon and Kodi
Version: @kodidevkit_VERSION_STRING@

Libs: -L${libdir} -lkodidevkit
Cflags: -I${includedir}
