cmake_minimum_required(VERSION 3.10)

project(SignalSlot)

file(GLOB_RECURSE SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.h)
	
add_executable(SignalSlot ${SOURCES})

set_target_properties(SignalSlot PROPERTIES CXX_STANDARD 17)
