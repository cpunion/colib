set(CMAKE_OSX_ARCHITECTURES x86_64;i386)

add_definitions(
-g -O2
)

add_library(co
	co.c
)

add_executable(cotest
	co.c
	cotest.c
)

add_executable(cotest1
	co.c
	cotest1.c
)

add_executable(cotest2
	co.c
	cotest2.c
)

