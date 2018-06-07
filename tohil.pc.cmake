#
# pkgconfig for Tohil
#

prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}
includedir=${prefix}/include/Tohil

Name: Tohil
Description: Tohil - A 2D game engine with integrated special effects.
Version: @VERSION_MAJOR@.@VERSION_MINOR@.@VERSION_PATCH@
Requires: @TH_PC_REQUIRES@
Libs: -L${libdir} -ltohil
Libs.private: -L${libdir} @TH_PC_LIBS@
Cflags: -I${includedir}
