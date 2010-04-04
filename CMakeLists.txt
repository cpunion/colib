cmake_minimum_required(VERSION 2.5)

set(CMAKE_OSX_ARCHITECTURES x86_64;i386)

add_definitions(
    -g -O3
)

include_directories(include)

set(LIBRARY_OUTPUT_PATH lib)
add_library(co
	src/co.c
    src/sched.c
    src/iosched.c
)

subdirs(tests)
