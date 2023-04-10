cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PROJECT_NAME crypto_lib_passwd)
set(CMAKE_C_STANDARD 99)

project(${PROJECT_NAME} VERSION 1 LANGUAGES C)

add_library(crypto_passwd SHARED
        src/crypto_lib_passwd.c
        src/aes.c
        src/base64.c)

add_executable(test_crypto
        utils/test_crypto.c
        src/crypto_lib_passwd.c
        src/aes.c
        src/base64.c)

target_link_libraries(crypto_passwd crypto)
target_link_libraries(test_crypto crypto)

install(DIRECTORY bin/ DESTINATION /usr/lib/)
