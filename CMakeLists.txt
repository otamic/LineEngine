cmake_minimum_required(VERSION 2.80)

project(GAME)

LINK_DIRECTORIES( ${CMAKE_SOURCE_DIR}/Libraries/libs )

find_package(OpenGL)

add_library(Engine
	src/Engine/engine.cpp
	src/Engine/glad.c
	src/Engine/object.cpp
	src/Engine/stb_image.cpp)
set(LIBS Engine ${OPENGL_LIBARIES} glfw3 assimp-vc120-mt irrKlang)

add_executable(GAME WIN32 src/game.cpp)
target_link_libraries(GAME ${LIBS})

include_directories( ${CMAKE_SOURCE_DIR}/Libraries/includes )
include_directories( src/Engine )

add_custom_command(TARGET GAME POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${CMAKE_SOURCE_DIR}/Libraries/libs/assimp-vc120-mt.dll"
	"${CMAKE_SOURCE_DIR}/Libraries/libs/glfw3.dll"
	"${CMAKE_SOURCE_DIR}/Libraries/libs/ikpMP3.dll"
	"${CMAKE_SOURCE_DIR}/Libraries/libs/irrKlang.dll"
	$<TARGET_FILE_DIR:GAME>)