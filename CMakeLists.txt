cmake_minimum_required(VERSION 2.8.11)

project(reactor1.0.0)

add_executable(reactor main.c diagnosticserver.c pollreactor.c tcpserver.c)

set(CMAKE_C_FLAGS "-std=c99") # that would be bad


