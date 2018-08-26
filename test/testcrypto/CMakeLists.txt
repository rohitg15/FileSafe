file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testcrypto ${SRCS})


# Include references to and link with openssl
include_directories("/usr/local/opt/openssl/include/")

# link_libraries("-lcrypto")
set(OPENSSL_CRYPTO_LIBRARY "/usr/local/opt/openssl/")

TARGET_LINK_LIBRARIES(testcrypto
    ${OPENSSL_CRYPTO_LIBRARY}/lib/libcrypto.a
    libcrypto
    libgtest
    libgmock
)

add_test(NAME testcrypto
         COMMAND testcrypto)
