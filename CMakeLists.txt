﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Introduction to Algorithms")

set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/)

# Include sub-projects.
add_subdirectory ("Chapter_02")
add_subdirectory ("Chapter_04")
add_subdirectory ("Chapter_06")
add_subdirectory ("Chapter_07")
add_subdirectory ("Chapter_08")
add_subdirectory ("Chapter_09")
add_subdirectory ("Chapter_10")
add_subdirectory ("Chapter_11")
add_subdirectory ("Chapter_12")
add_subdirectory ("Chapter_13")
add_subdirectory ("Chapter_14")
add_subdirectory ("Chapter_15")
add_subdirectory ("Chapter_16")
add_subdirectory ("Chapter_19")
add_subdirectory ("Chapter_22")
add_subdirectory ("Chapter_23")
add_subdirectory ("Chapter_24")
add_subdirectory ("Chapter_25")
add_subdirectory ("Chapter_26")
