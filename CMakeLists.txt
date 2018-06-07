cmake_minimum_required(VERSION 2.8)

project(TOHIL)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)
set(VERSION_BUILD 0)

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(PACKAGE "tohil-${VERSION_STRING}")

option(BUILD_SHARED_LIBS "Build shared libraries." ON)
option(FORCE_32BIT "Force 32 bit build." OFF)

# For some reason, we can't call find_package(SDL) more than once in one
# project with MXE, so we need to do this on the top level...
#
# Also, since FindSDL2.cmake still doesn't seem to be included in distros as
# I'm writing this, we're sticking with pkg_search_module(), which relies on
# pkg-config instead of CMake specific scripts.

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
set(TH_PC_REQUIRES "sdl2 >= 2.0.0")
set(TH_PC_LIBS "-lSDL2")

if(NOT WIN32 AND NOT BUILD_SHARED_LIBS)
	set(TOHIL_EXTRA_LIBRARIES "${TH_PC_LIBS} -ldl -lm")
endif()

add_subdirectory(src)
add_subdirectory(test)

configure_file(include/tohil.h.cmake
	${TOHIL_BINARY_DIR}/include/tohil.h @ONLY)
install(FILES ${TOHIL_BINARY_DIR}/include/tohil.h
	DESTINATION include/Tohil)
install(DIRECTORY include/ DESTINATION include/Tohil
	FILES_MATCHING PATTERN "*.h")

configure_file(tohil.pc.cmake ${TOHIL_BINARY_DIR}/tohil.pc
	@ONLY)
install(FILES ${TOHIL_BINARY_DIR}/tohil.pc
	DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/")

# CPack general
set(CPACK_GENERATOR "DEB" "RPM" "TBZ2")
set(CPACK_SET_DESTDIR ON)
set(CPACK_PACKAGE_RELOCATABLE "false")
set(CPACK_PACKAGE_NAME "tohil")
set(CPACK_PACKAGE_VERSION "${VERSION_STRING}")
set(CPACK_PACKAGE_CONTACT "David Olofson <david@olofson.net>")
set(CPACK_RESOURCE_FILE_LICENSE "${TOHIL_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${TOHIL_SOURCE_DIR}/README.md")

# CPack DEB
set(CPACK_DEBIAN_PACKAGE_SECTION "Libraries")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl2")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION_SUMMARY "A 2D game engine with integrated special effects")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Tohil is a 3D accelerated 2D game engine with integrated special effects, primarily intended for the game Kobo Redux, but being developed and maintained as a separate project.")

# CPack PRM
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_PACKAGE_SUMMARY "${CPACK_DEBIAN_PACKAGE_DESCRIPTION_SUMMARY}")
set(CPACK_RPM_PACKAGE_DESCRIPTION "${CPACK_DEBIAN_PACKAGE_DESCRIPTION}")
set(CPACK_RPM_PACKAGE_LICENSE "zlib")
set(CPACK_RPM_PACKAGE_REQUIRES "libSDL2-2.0.so.0,libm.so.6")

include(CPack)
