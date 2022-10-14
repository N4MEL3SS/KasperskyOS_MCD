cmake_minimum_required(VERSION 3.24)
project(KasperskyOS_MCD)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -Werror)

set(SERVER Server/main.cpp Server/Server.cpp Server/Server.hpp Server/easylogging++.cc Server/easylogging++.h)

set(CLIENT Client/main.cpp Client/Client.cpp Client/Client.hpp)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(Server ${SERVER})
add_executable(Client ${CLIENT})
if(TARGET Threads::Threads)
	target_link_libraries(Server PRIVATE Threads::Threads)
endif()
