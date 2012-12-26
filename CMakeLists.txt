project(tcpserver)

add_executable(tcpserver main.cpp)

install(TARGETS tcpserver RUNTIME DESTINATION bin)
