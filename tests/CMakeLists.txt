
link_directories(../lib)
link_libraries(co)

add_executable(cotest
	cotest.c
)
add_executable(cobench
	cobench.c
)
add_executable(schedtest
    schedtest.c
)
add_executable(schedbench
    schedbench.c
)
add_executable(schedspawn
    schedspawn.c
)
add_executable(schedlargebench
    schedlargebench.c
)

