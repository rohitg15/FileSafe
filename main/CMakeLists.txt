set(Main_SRCS
    main.cpp
)

add_executable(myApp
    ${Main_SRCS}
)

find_package(Threads)

# Specify here the libraries this program depends on
target_link_libraries(myApp
    # libfoo
    # libtls
    # libsocket
    libthreads
    ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS myApp DESTINATION bin)
