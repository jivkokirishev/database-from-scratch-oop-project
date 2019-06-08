cmake_minimum_required(VERSION 3.14)
project(database_from_scratch_oop_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(database_from_scratch_oop_project main.cpp
        src/collections/Collection.cpp
        src/collections/doubly_linked_list/DoublyLinkedList.cpp
        src/database_components/abstracts/Column.cpp
        src/database_components/abstracts/Column.h
        src/database_components/enums/ColumnType.cpp
        src/database_components/abstracts/Type.cpp
        src/database_components/implementations/Integer.cpp
        src/database_components/implementations/Integer.h
        src/database_components/implementations/Real.cpp
        src/database_components/implementations/Real.h
        src/database_components/implementations/String.cpp
        src/database_components/implementations/String.h
        src/database_components/implementations/Table.cpp
        src/database_components/implementations/Table.h
        src/database_components/implementations/StringColumn.cpp
        src/database_components/implementations/StringColumn.h
        src/database_components/implementations/RealNumberColumn.cpp
        src/database_components/implementations/RealNumberColumn.h
        src/database_components/implementations/IntegerColumn.cpp
        src/database_components/implementations/IntegerColumn.h
        src/database_components/implementations/Database.cpp
        src/database_components/implementations/Database.h
        src/database_manager/DbStreamManager.cpp
        src/database_manager/DbStreamManager.h
        src/database_manager/enums/OperationType.cpp
        src/database_manager/AggregationOperations.cpp
        src/database_manager/AggregationOperations.h
        src/database_manager/DbFileManager.cpp
        src/database_manager/DbFileManager.h
        src/ux_components/CommandParser.cpp
        src/ux_components/CommandParser.h
        src/ux_components/ConsoleLauncher.cpp
        src/ux_components/ConsoleLauncher.h)
