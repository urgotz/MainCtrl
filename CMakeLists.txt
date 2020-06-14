cmake_minimum_required (VERSION 3.8)
project(camera_server)

# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O3 -lpthread")

include_directories(
	include
	)

add_executable (MainCtrl 
	src/MainCtrl.cpp
	src/MainCtrlTest.cpp
	)


target_link_libraries(MainCtrl
	-lpthread
	)



