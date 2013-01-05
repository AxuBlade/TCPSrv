cmake_minimum_required(VERSION 2.8)
project(tcpserver)

add_executable(tcpserver main.c)
install(TARGETS tcpserver RUNTIME DESTINATION bin)
