cmake_minimum_required(VERSION 2.8)
project(tcpserver)

add_executable(tcpserver main_srv.c)
install(TARGETS tcpserver RUNTIME DESTINATION bin)
