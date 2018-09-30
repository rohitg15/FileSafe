set(libcrypto_SRCS
    cryptoalgorithms.h
    cryptoalgorithms.cpp
    hmacprovider.h
    hmacprovider.cpp
)

# include_directories("/usr/local/opt/openssl/include")


find_package(OpenSSL)

set(OPENSSL_CRYPTO_LIBRARY "/usr/lib/x86_64-linux-gnu")

link_libraries("-lcrypto")

# Declare the library
add_library(libcrypto STATIC
    ${libcrypto_SRCS}
)


# Specify here the include directories exported
# by this library
target_include_directories(libcrypto PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)