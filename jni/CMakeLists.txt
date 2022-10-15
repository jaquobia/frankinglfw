cmake_minimum_required(VERSION 3.20.0)
project(FrankinGlfw VERSION 0.1.2)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../src/main/resources)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_USE_WAYLAND ON CACHE BOOL "" FORCE)
add_subdirectory(glfw)
add_library(FrankinGlfw SHARED io_github_jaquobia_Glfw.cpp)
target_link_libraries(FrankinGlfw glfw)
set_target_properties(FrankinGlfw PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
include(CPack)
