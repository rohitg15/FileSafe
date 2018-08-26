set(libcrypto_SRCS
    cryptoalgorithms.h
    cryptoalgorithms.cpp
    hmacprovider.h
    hmacprovider.cpp
)

include_directories("/usr/local/opt/openssl/include")

# Declare the library
add_library(libcrypto STATIC
    ${libcrypto_SRCS}
)

link_libraries("-lcrypto")

# Specify here the include directories exported
# by this library
target_include_directories(libcrypto PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
