CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )

PROJECT( CameraStreaming VERSION 1.0 )

SET( CMAKE_CXX_STANDARD 11 )

FIND_PACKAGE( OpenCV REQUIRED )
FIND_PACKAGE( Boost 1.71 COMPONENTS filesystem program_options REQUIRED )

SET( TARGET_LIBS ${TARGET_LIBS} camera_streaming )
SET( TARGET_LIBS ${TARGET_LIBS} ${OpenCV_LIBS} )
SET( TARGET_LIBS ${TARGET_LIBS} ${Boost_LIBRARIES} )

INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/inc
	${PROJECT_SOURCE_DIR}/src
	${OpenCV_INCLUDE_DIRS}
	)

FILE(GLOB ALL_SOURCES
	"${PROJECT_SOURCE_DIR}/inc/application/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/application/*.cpp"
	"${PROJECT_SOURCE_DIR}/inc/camera/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/camera/*.cpp"
	"${PROJECT_SOURCE_DIR}/inc/system/*.hpp"
	)

SET( EXEC_PATH "${CMAKE_CURRENT_BINARY_DIR}/CameraStreaming_bin $@" )

WRITE_FILE(
	${CMAKE_CURRENT_BINARY_DIR}/CameraStreaming
	"#!/bin/bash\n\n${EXEC_PATH}\nwhile [[ $? -eq 141 ]]\ndo\n\t${EXEC_PATH}\ndone"
	)

EXECUTE_PROCESS(
	COMMAND bash -c "chmod +x ${CMAKE_CURRENT_BINARY_DIR}/CameraStreaming"
	)

ADD_LIBRARY( camera_streaming SHARED ${ALL_SOURCES} )
ADD_EXECUTABLE( CameraStreaming_bin "${PROJECT_SOURCE_DIR}/src/main.cpp" )

TARGET_LINK_LIBRARIES( CameraStreaming_bin ${TARGET_LIBS} )
