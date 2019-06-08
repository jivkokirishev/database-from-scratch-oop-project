//
// Created by jivko on 19.05.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_DATABASE_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_DATABASE_H

#include <vector>
#include <string>
#include "Table.h"

namespace db_components {
    namespace implementation {
        class Database {
        private:
            std::string name;
            std::vector<Table *> tables;

        public:
            Database(std::string name);

            void AddTable(std::string tableName);

            bool TableExist(std::string name);

            Table &GetTableAt(int index);

            Table &GetTableByName(std::string const &name);

            void DeleteTableAt(int index);

            void DeleteTableByName(std::string const &name);

            void SetName(std::string name);

            std::string GetName() const;

            int TableCount() const;

            ~Database();
        };
    }
}
#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_DATABASE_H
