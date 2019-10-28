CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

file(GLOB_RECURSE PONG_SRC *.c)
file(GLOB_RECURSE PONG_H *.h)

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
)

if(APPLE)
	add_executable(
		Pong 
		MACOSX_BUNDLE 
		${PONG_H}
		${PONG_SRC}
		)
else()
	add_executable(Pong ${PONG_H} ${PONG_SRC})
endif()

if(APPLE)
	find_path(COCOA_INCLUDE_DIR Cocoa/Cocoa)
	find_library(COCOA_LIBRARY Cocoa)

	target_link_libraries (Pong ${COCOA_LIBRARY})
endif()

target_link_libraries (Pong LINK_PUBLIC SWin SText)
