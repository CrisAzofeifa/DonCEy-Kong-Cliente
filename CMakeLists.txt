cmake_minimum_required(VERSION 3.14)
project(CEDK_Client C)

set(CMAKE_C_STANDARD 99)

add_executable(CEDK_Client main.c)

find_package(SDL2 REQUIRED)
include_directories("usr/include/SDL2")
target_link_libraries(CEDK_Client ${SDL2_LIBRARY} -lSDL2)
target_link_libraries(CEDK_Client ${SDL2_LIBRARY}-lSDL2_mixer)
target_link_libraries(CEDK_Client ${SDL2_image_LIBRARY} -lSDL2_image)
