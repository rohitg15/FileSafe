cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)
set (CXX_DEFINES -std=c++11)

find_package(OpenSSL)

project(myProject)

enable_testing()

add_subdirectory(main)
# add_subdirectory(libfoo)
# add_subdirectory(libtls)
# add_subdirectory(libsocket)
add_subdirectory(libthreads)
add_subdirectory(libcrypto)
add_subdirectory(test)
