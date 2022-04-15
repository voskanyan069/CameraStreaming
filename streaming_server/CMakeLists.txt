INCLUDE ( ../common.cmake )

CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )

PROJECT( CameraStreaming VERSION 1.0 )

FIND_PACKAGE( OpenCV REQUIRED )
FIND_PACKAGE( Boost 1.71 COMPONENTS filesystem program_options REQUIRED )

SET( TARGET_LIBS ${TARGET_LIBS} camera_streaming_server )
SET( TARGET_LIBS ${TARGET_LIBS} ${Base_LIBRARIES} )
SET( TARGET_LIBS ${TARGET_LIBS} ${OpenCV_LIBS} )
SET( TARGET_LIBS ${TARGET_LIBS} ${Boost_LIBRARIES} )

INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/inc
	${PROJECT_SOURCE_DIR}/src
	${Base_INCLUDE_DIR}
	${OpenCV_INCLUDE_DIRS}
	)

FILE(GLOB ALL_SOURCES
	"${PROJECT_SOURCE_DIR}/src/application/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/camera/*.cpp"
	)

SET(
	EXEC_PATH
	"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CameraStreamingServer_bin $@"
	)

WRITE_FILE(
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CameraStreamingServer
	"#!/bin/bash\n\n${EXEC_PATH}\nwhile [[ $? -eq 141 ]]\ndo\n\t${EXEC_PATH}\ndone"
	)

EXECUTE_PROCESS(
	COMMAND
	bash -c "chmod +x ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CameraStreamingServer"
	)

ADD_LIBRARY( camera_streaming_server SHARED ${ALL_SOURCES} )
ADD_EXECUTABLE( CameraStreamingServer_bin "${PROJECT_SOURCE_DIR}/src/main.cpp" )

TARGET_LINK_LIBRARIES( CameraStreamingServer_bin ${TARGET_LIBS} )
