# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_07")

set (CMAKE_C_STANDARD 99)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)

set (FILE_NAME QuickSort_main)
set (SOURCE_C_LIST ${FILE_NAME}.c QuickSort.c)
set (FILE_NAME_2 RandomizedQuickSort_main)
set (SOURCE_C_LIST_2 ${FILE_NAME_2}.c RandomizedQuickSort.c)
set (FILE_NAME_3 HoareQuickSort_main)
set (SOURCE_C_LIST_3 ${FILE_NAME_3}.c HoareQuickSort.c)
set (FILE_NAME_4 EnhancedRandomizedQuickSort_main)
set (SOURCE_C_LIST_4 ${FILE_NAME_4}.c EnhancedRandomizedQuickSort.c)
set (FILE_NAME_5 TailRecursiveQuickSort_main)
set (SOURCE_C_LIST_5 ${FILE_NAME_5}.c TailRecursiveQuickSort.c)

# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_C_LIST})
add_executable (${FILE_NAME_2} ${SOURCE_C_LIST_2})
add_executable (${FILE_NAME_3} ${SOURCE_C_LIST_3})
add_executable (${FILE_NAME_4} ${SOURCE_C_LIST_4})
add_executable (${FILE_NAME_5} ${SOURCE_C_LIST_5})

# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} DESTINATION Build)
install (TARGETS ${FILE_NAME_2} DESTINATION Build)
install (TARGETS ${FILE_NAME_3} DESTINATION Build)
install (TARGETS ${FILE_NAME_4} DESTINATION Build)
install (TARGETS ${FILE_NAME_5} DESTINATION Build)
