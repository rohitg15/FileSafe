file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testthreads ${SRCS})

TARGET_LINK_LIBRARIES(testthreads
    libthreads
    libgtest
    libgmock
)

add_test(NAME testthreads
         COMMAND testthreads)
