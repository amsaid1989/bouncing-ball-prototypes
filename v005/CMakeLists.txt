cmake_minimum_required(VERSION 3.10)

project(Boink)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(Boink Game.cpp rendering.cpp main.cpp)

target_include_directories(Boink PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(Boink ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
