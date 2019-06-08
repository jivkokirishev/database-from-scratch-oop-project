//
// Created by jivko on 27.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_TABLE_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_TABLE_H

#include "../../collections/Collection.cpp"
#include "../../collections/doubly_linked_list/DoublyLinkedList.cpp"
#include "../enums/ColumnType.cpp"
#include "../abstracts/Column.h"

#include <vector>
#include <string>

namespace db_components {
    namespace implementation {

        class Table {
        private:
            std::string name;
            std::vector<abstract::Column *> columns;

        protected:
            void Copy(Table const &table);

        public:
            Table(std::string name);

            Table(Table const &table);

            Table &operator=(Table const &table);

            void AddColumn(enums::ColumnType columnType, std::string columnName);

            void InsertRow(std::vector<std::string> const &row);

            abstract::Column *GetColumnAt(int index);

            void DeleteColumnAt(int index);

            void SetName(std::string name);

            std::string GetName() const;

            int ColumnCount() const;

            ~Table();
        };
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_TABLE_H
