cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project(myProject)

enable_testing()

add_subdirectory(main)
# add_subdirectory(libfoo)
# add_subdirectory(libtls)
# add_subdirectory(libsocket)
add_subdirectory(libthreads)
add_subdirectory(test)
