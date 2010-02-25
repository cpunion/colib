cmake_minimum_required(VERSION 2.5)

set(CMAKE_OSX_ARCHITECTURES x86_64;i386)

add_definitions(
-g -O2
)

add_library(co
	co.c
)

link_libraries(co)
add_executable(cotest
	cotest.c
)

