# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_09")

set (CMAKE_C_STANDARD 99)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)

set (FILE_NAME MinimumMaximum_main)
set (SOURCE_C_LIST ${FILE_NAME}.c MinimumMaximum.c)

# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_C_LIST})

# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} DESTINATION Build)
