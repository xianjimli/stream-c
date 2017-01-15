cmake_minimum_required(VERSION 2.8)

project(stream)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/demos)
include_directories(${PROJECT_SOURCE_DIR}/serial/src)
include_directories(${PROJECT_SOURCE_DIR}/serial/include)
include_directories(${PROJECT_SOURCE_DIR}/serial/src/impl)
include_directories(${PROJECT_SOURCE_DIR}/serial/src/impl/list_ports)

set(PLATFORM_SRC )
if(APPLE)
	# If OSX
	list(APPEND PLATFORM_SRC serial/src/impl/unix.cc)
	list(APPEND PLATFORM_SRC serial/src/impl/list_ports/list_ports_osx.cc)
	find_library(IOKIT_LIBRARY IOKit)
	find_library(FOUNDATION_LIBRARY Foundation)

	set(PLATFORM_LIB ${IOKIT_LIBRARY} ${FOUNDATION_LIBRARY})
	ADD_DEFINITIONS(-g -W -Wall)
elseif(UNIX)
    # If unix
    list(APPEND PLATFORM_SRC serial/src/impl/unix.cc)
    list(APPEND PLATFORM_SRC serial/src/impl/list_ports/list_ports_linux.cc)
	ADD_DEFINITIONS(-g -W -Wall)
else()
    # If windows
    list(APPEND PLATFORM_SRC serial/src/impl/win.cc)
    list(APPEND PLATFORM_SRC serial/src/impl/list_ports/list_ports_win.cc)
	ADD_DEFINITIONS(-W0)
endif()

set(COMMON_SRC
	src/platform.c
	src/istream_file.c	
	src/ostream_file.c	
	src/stream_tcp.c
	src/stream_log.c
	src/stream_serial.cpp
)

add_library(${PROJECT_NAME} ${PLATFORM_SRC} ${COMMON_SRC})
if(APPLE)
	target_link_libraries(${PROJECT_NAME} ${FOUNDATION_LIBRARY} ${IOKIT_LIBRARY})
elseif(UNIX)
	target_link_libraries(${PROJECT_NAME} rt pthread)
else()
	target_link_libraries(${PROJECT_NAME} setupapi ws2_32)
endif()

set(FILE_COPY_SRC demos/file_copy.c)
add_executable(file_copy ${FILE_COPY_SRC})
target_link_libraries(file_copy ${PROJECT_NAME})

set(SERVER_SRC demos/server.c)
add_executable(server ${SERVER_SRC})
target_link_libraries(server ${PROJECT_NAME})

set(CLIENT_SRC demos/client.c)
add_executable(client ${CLIENT_SRC})
target_link_libraries(client ${PROJECT_NAME})
