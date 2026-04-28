cmake_minimum_required(VERSION 3.20)
project(SnakeSFML)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(SnakeSFML
        main.cpp
        Snake.cpp
        Direction.h
        Snake.h
)

target_link_libraries(SnakeSFML SFML::Graphics SFML::Window SFML::System)