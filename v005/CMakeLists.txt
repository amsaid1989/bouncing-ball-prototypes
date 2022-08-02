cmake_minimum_required(VERSION 3.10)

project(Boink)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(Boink Game.cpp rendering.cpp main.cpp)

target_include_directories(Boink PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(Boink PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

install(TARGETS Boink DESTINATION bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/circle.png DESTINATION bin)
install(
	FILES
		${CMAKE_CURRENT_SOURCE_DIR}/constants.h
		${CMAKE_CURRENT_SOURCE_DIR}/rendering.h
		${CMAKE_CURRENT_SOURCE_DIR}/Game.h
	DESTINATION
		include
)
install(
	FILES
		/usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0.10.0
		/usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0.2.3
		/usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0
		/usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0
	DESTINATION
		lib
)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
