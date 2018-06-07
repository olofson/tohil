include(CheckIncludeFiles)

include_directories(${TOHIL_BINARY_DIR}/include)
include_directories(${TOHIL_SOURCE_DIR}/include)
include_directories(${TOHIL_SOURCE_DIR}/src)


# Core files
set(sources
	tohil.c
	state.c
)


include_directories(${SDL2_INCLUDE_DIRS})

add_library(tohil ${sources})
if(FORCE_32BIT)
	set_target_properties(tohil PROPERTIES
		COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT)

if(UNIX)
	target_link_libraries(tohil m)
endif(UNIX)

target_link_libraries(tohil ${SDL2_LIBRARIES})

set_target_properties(tohil PROPERTIES VERSION ${VERSION_STRING}
	SOVERSION ${VERSION_STRING})

# Release build: full optimization, no debug features, no debug info
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# Static release build: full optimization, no debug features, no debug info
set(CMAKE_C_FLAGS_STATIC "-O3 -DNDEBUG")

set(f "-Wall -Wwrite-strings -Wcast-align")
set(f "${f} -Wbad-function-cast -Waggregate-return")
set(f "${f} -Wstrict-prototypes -fno-builtin -Wshadow")
set(f "${f} -Wdeclaration-after-statement -Wmissing-prototypes")
set(f "${f} -Wmissing-declarations -Wdisabled-optimization")
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
	set(f "${f} -Wincompatible-pointer-types")
endif()

# Debug build: No optimizations, extra debug features, don't fail on warnings
set(CMAKE_C_FLAGS_DEBUG "${f} -O0 -g -DDEBUG")

# Maintainer build: Few optimizations, lots of warnings, fail on warnings
set(CMAKE_C_FLAGS_MAINTAINER "${f} -O1 -g -Werror")

install(TARGETS tohil DESTINATION lib)
