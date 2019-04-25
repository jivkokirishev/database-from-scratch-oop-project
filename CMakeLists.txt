cmake_minimum_required(VERSION 3.14)
project(database_from_scratch_oop_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(database_from_scratch_oop_project main.cpp src/collections/Collection.cpp src/collections/doubly_linked_list/DoublyLinkedList.cpp)