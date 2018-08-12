set(Main_SRCS
    main.cpp
)

add_executable(myApp
    ${Main_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(myApp
    # libfoo
    # libtls
    # libsocket
    libthreads
)

install(TARGETS myApp DESTINATION bin)
