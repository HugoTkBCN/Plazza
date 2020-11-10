cmake_minimum_required(VERSION 3.16)
project(CCP_plazza_2019)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(CCP_plazza_2019
        include/command.hpp
        include/Kitchen.hpp
        include/LoadBalancer.hpp
        include/Pizza.hpp
        include/Plazza.hpp
        include/Reception.hpp
        include/Utils.hpp
        src/Kitchen.cpp
        src/LoadBalancer.cpp
        src/Pizza.cpp
        src/Reception.cpp
        src/Utils.cpp
        main.cpp)
