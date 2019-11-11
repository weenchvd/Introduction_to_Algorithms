# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_10")

set (CMAKE_C_STANDARD 99)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)

set (FILE_NAME StackQueue_main)
set (SOURCE_C_LIST ${FILE_NAME}.c StackQueue.c)
set (FILE_NAME_2 LinkedList_main)
set (SOURCE_C_LIST_2 ${FILE_NAME_2}.c LinkedList.c)
set (FILE_NAME_3 PointersObjects_main)
set (SOURCE_C_LIST_3 ${FILE_NAME_3}.c PointersObjects.c)
set (FILE_NAME_4 BinaryTree_main)
set (SOURCE_C_LIST_4 ${FILE_NAME_4}.c BinaryTree.c)

# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_C_LIST})
add_executable (${FILE_NAME_2} ${SOURCE_C_LIST_2})
add_executable (${FILE_NAME_3} ${SOURCE_C_LIST_3})
add_executable (${FILE_NAME_4} ${SOURCE_C_LIST_4})

# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME_2} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME_2} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME_3} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME_3} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME_4} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME_4} CONFIGURATIONS Release DESTINATION Build)
