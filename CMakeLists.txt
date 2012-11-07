project(Presquile)

cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

if (CMAKE_BUILD_TYPE MATCHES Debug)
  add_definitions(-DDEBUG_MODE)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

add_subdirectory(src)
add_subdirectory(data)