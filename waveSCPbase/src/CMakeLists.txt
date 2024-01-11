cmake_minimum_required(VERSION 3.4)
project(wavescp)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OPENSSL_USE_STATIC_LIBS TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -DINFO_IS_ON=0 -DDEBUG_IS_ON=0 -DTRACE_IS_ON=1")

find_package(OpenSSL REQUIRED)

find_library(PISTACHE_LIBRARY pistache)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/app)
include_directories(${CMAKE_SOURCE_DIR}/libs/)


add_subdirectory(app)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./)

target_link_directories(${PROJECT_NAME} PUBLIC app/)

target_link_libraries(${PROJECT_NAME} FUNC)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} curl)
target_link_libraries(${PROJECT_NAME} ${PISTACHE_LIBRARY})
