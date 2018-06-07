# For stand-alone build, linking to the system Tohil library
#find_package(Tohil REQUIRED)
#include_directories(${TOHIL_INCLUDE_DIR})

# For local build, not relying on an installed library
include_directories(${TOHIL_BINARY_DIR}/include)
include_directories(${TOHIL_SOURCE_DIR}/include)
link_directories(${TOHIL_BINARY_DIR})
set(TOHIL_LIBRARIES tohil ${TOHIL_EXTRA_LIBRARIES})

function(th_add_test testname)
	add_executable(${testname} WIN32 MACOSX_BUNDLE ${testname}.c ${ARGN})
	target_link_libraries(${testname} ${TOHIL_LIBRARIES})
	if(FORCE_32BIT)
		set_target_properties(${testname} PROPERTIES
			COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
	endif(FORCE_32BIT)
endfunction(th_add_test)

th_add_test(hello)

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
