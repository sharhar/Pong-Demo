CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

PROJECT(Pong)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_VERBOSE_MAKEFILE ON)

option(SWIN_BUILD_TEST OFF)
option(STEXT_BUILD_TEST OFF)

include_directories(
	"${CMAKE_SOURCE_DIR}/SWin/include"
	"${CMAKE_SOURCE_DIR}/SText/include"
)

add_subdirectory(SWin)
add_subdirectory(SText)
add_subdirectory(src)