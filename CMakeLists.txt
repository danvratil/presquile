project(Presquile)

cmake_minimum_required(VERSION 2.6)

set(PRESQUILE_VERSION_MAJOR 0)
set(PRESQUILE_VERSION_MINOR 1)
set(PRESQUILE_VERSION_RELEASE 0)
set(PRESQUILE_VERSION "${PRESQUILE_VERSION_MAJOR}.${PRESQUILE_VERSION_MINOR}.${PRESQUILE_VERSION_RELEASE}")

set(CMAKE_AUTOMOC ON)

include(GenerateExportHeader)

find_package(Qt4 REQUIRED)
add_definitions(${QT_DEFINITIONS}
                -DQT_USE_QSTRINGBUILDER
                -DQT_NO_CAST_TO_ASCII
                -DQT_NO_CAST_FROM_ASCII
                -DQT_NO_KEYWORDS
                -DQT_USE_FAST_COONCATENATION
                -DQT_USE_FAST_OPERATOR_PLUS
)

set(BIN_INSTALL_DIR "bin")
set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)")
set(LIB_INSTALL_DIR "lib${LIB_SUFFIX}")
set(INCLUDE_INSTALL_DIR "include/Presquile")
set(CMAKECONFIG_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/Presquile)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${BIN_INSTALL_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${LIB_INSTALL_DIR})
if (NOT DEFINED PRESQUILE_IMPORTS_INSTALL_DIR)
    set(PRESQUILE_IMPORTS_INSTALL_DIR "${LIB_INSTALL_DIR}/qt4/imports/")
endif()

# set RPATH only when installing to a non-default location
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}" _isSystemPlatformLibDir)
list(FIND CMAKE_C_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}" _isSystemCLibDir)
list(FIND CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}" _isSystemCxxLibDir)
if(${_isSystemPlatformLibDir} EQUAL -1 AND ${_isSystemCLibDir} EQUAL -1 AND ${_isSystemCxxLibDir} EQUAL -1)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}")
endif()

set(INSTALL_TARGETS_DEFAULT_ARGS
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT Devel
    BUNDLE DESTINATION "/Applications/Qt4"
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_C_COMPILER MATCHES "icc" OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
  # more aggressive warnings and C++11 support
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wno-long-long -std=iso9899:1990 -Wundef -Wcast-align -Werror-implicit-function-declaration -Wchar-subscripts -Wall -Wextra -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -fno-common")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wnon-virtual-dtor -Wundef -Wcast-align -Wchar-subscripts -Wall -Wextra -Wpointer-arith -Wformat-security -fno-common")
endif()

add_subdirectory(src)
add_subdirectory(tests)
