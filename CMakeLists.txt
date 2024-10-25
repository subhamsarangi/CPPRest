cmake_minimum_required(VERSION 3.10)

project(cpprest_example)

set(CMAKE_CXX_STANDARD 11)

find_package(cpprestsdk REQUIRED)

find_package(OpenSSL REQUIRED)

add_executable(cpprest_example main.cpp)

target_link_libraries(cpprest_example PRIVATE cpprest OpenSSL::SSL OpenSSL::Crypto)
