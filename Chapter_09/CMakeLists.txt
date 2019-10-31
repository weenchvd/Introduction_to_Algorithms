# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_09")

set (CMAKE_C_STANDARD 99)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)

set (FILE_NAME MinimumMaximum_main)
set (SOURCE_C_LIST ${FILE_NAME}.c MinimumMaximum.c)
set (FILE_NAME_2 RandomizedSelect_main)
set (SOURCE_C_LIST_2 ${FILE_NAME_2}.c RandomizedSelect.c)
set (FILE_NAME_3 Select_main)
set (SOURCE_C_LIST_3 ${FILE_NAME_3}.c Select.c)
set (FILE_NAME_4 QuickSortMedian_main)
set (SOURCE_C_LIST_4 ${FILE_NAME_4}.c QuickSortMedian.c)

# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_C_LIST})
add_executable (${FILE_NAME_2} ${SOURCE_C_LIST_2})
add_executable (${FILE_NAME_3} ${SOURCE_C_LIST_3})
add_executable (${FILE_NAME_4} ${SOURCE_C_LIST_4})

# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} DESTINATION Build)
install (TARGETS ${FILE_NAME_2} DESTINATION Build)
install (TARGETS ${FILE_NAME_3} DESTINATION Build)
install (TARGETS ${FILE_NAME_4} DESTINATION Build)
