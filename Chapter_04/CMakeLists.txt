﻿# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_04")

set (CMAKE_C_STANDARD 99)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)

set (FILE_NAME FindMaximumSubarray_main)
set (SOURCE_C_LIST ${FILE_NAME}.c FindMaximumSubarray.c)
#set (FILE_NAME_2 SquareMatrixMultiply_main)
#set (SOURCE_C_LIST_2 ${FILE_NAME_2}.c SquareMatrixMultiply.c)

# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_C_LIST})
#add_executable (${FILE_NAME_2} ${SOURCE_C_LIST_2})

# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} DESTINATION Build)
#install (TARGETS ${FILE_NAME_2} DESTINATION Build)
