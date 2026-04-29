cmake_minimum_required(VERSION 3.20)
project(SnakeSFML)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(SnakeSFML
        src/main.cpp
        include/Direction.h
        src/Snake.cpp
        include/Snake.h
        src/Apple.cpp
        include/Apple.h
        src/Window.cpp
        include/Window.h
)

target_link_libraries(SnakeSFML SFML::Graphics SFML::Window SFML::System)