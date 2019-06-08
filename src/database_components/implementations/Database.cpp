//
// Created by jivko on 19.05.19.
//

#include "Database.h"

namespace db_components {
    namespace implementation {
        Database::Database(std::string name) {
            this->SetName(name);
            this->tables = std::vector<Table *>();
        }

        void Database::SetName(std::string name) {
            this->name = name;
        }

        std::string Database::GetName() const {
            return this->name;
        }

        void Database::AddTable(std::string tableName) {
            Table *table = new Table(tableName);

            this->tables.push_back(table);
        }

        Table &Database::GetTableAt(int index) {
            return *this->tables[index];
        }

        void Database::DeleteTableAt(int index) {
            this->tables.erase(tables.begin() + index);
        }

        int Database::TableCount() const {
            return this->tables.size();
        }

        Database::~Database() {
        }

        Table &Database::GetTableByName(std::string const &name) {
            int tableCounter = 0;
            while (tableCounter < this->TableCount() && name != this->GetTableAt(tableCounter).GetName()) {
                tableCounter++;
            }
            Table &table = this->GetTableAt(tableCounter);

            return table;
        }

        bool Database::TableExist(std::string name) {
            int tableCounter = 0;
            while (tableCounter < this->TableCount() && name != this->GetTableAt(tableCounter).GetName()) {
                tableCounter++;
            }

            if (tableCounter < this->TableCount()) {
                return true;
            }

            return false;
        }

        void Database::DeleteTableByName(std::string const &name) {
            int tableCounter = 0;
            while (tableCounter < this->TableCount() && name != this->GetTableAt(tableCounter).GetName()) {
                tableCounter++;
            }
            this->DeleteTableAt(tableCounter);
        }
    }
}
