//
// Created by jivko on 27.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_TABLE_CPP
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_TABLE_CPP

#include "Table.h"
#include "IntegerColumn.h"
#include "RealNumberColumn.h"
#include "StringColumn.h"

namespace db_components {
    namespace implementation {


        void Table::SetName(std::string name) {
            this->name = name;
        }

        std::string Table::GetName() const {
            return this->name;
        }

        Table::Table(std::string name) {
            this->SetName(name);
            this->columns = std::vector<abstract::Column *>();
        }

        void Table::Copy(const Table &table) {
            columns.clear();

            this->SetName(table.name);
        }

        Table::Table(Table const &table) {
            this->Copy(table);

        }

        Table &Table::operator=(Table const &table) {
            if (this != &table) {
                Copy(table);
            }
            return *this;
        }

        Table::~Table() {
            columns.clear();
        }

        void Table::AddColumn(enums::ColumnType columnType, std::string columnName) {

            abstract::Column *column;

            switch (columnType) {
                case enums::integerNumber: {
                    column = new IntegerColumn(columnName.c_str());
                }
                    break;
                case enums::realNumber: {
                    column = new RealNumberColumn(columnName.c_str());
                }
                    break;
                case enums::string: {
                    column = new StringColumn(columnName.c_str());
                }
                    break;
                default:
                    return;
            }

            this->columns.push_back(column);
        }

        abstract::Column *Table::GetColumnAt(int index) {

            if (index >= this->ColumnCount()) {
                throw std::out_of_range("There is not any column with this index. The max column index is :" +
                                        std::to_string(this->ColumnCount()));
            }

            return this->columns[index];
        }

        void Table::DeleteColumnAt(int index) {

            if (index >= this->ColumnCount()) {
                throw std::out_of_range("There is not any column with this index. The max column index is :" +
                                        std::to_string(this->ColumnCount()));
            }

            this->columns.erase(columns.begin() + index);
        }

        int Table::ColumnCount() const {
            return this->columns.size();
        }

        void Table::InsertRow(std::vector<std::string> const &row) {

            for (int i = 0; i < this->ColumnCount(); ++i) {

                db_components::abstract::Type *cell;

                switch (this->GetColumnAt(i)->GetType()) {
                    case db_components::enums::integerNumber : {
                        cell = new db_components::implementation::Integer();
                    }
                        break;
                    case db_components::enums::realNumber : {
                        cell = new db_components::implementation::Real();
                    }
                        break;
                    case db_components::enums::string : {
                        cell = new db_components::implementation::String();
                    }
                        break;
                }

                if (row[i] == "NULL") {
                    cell->SetIsNullTrue();
                } else {
                    cell->SetValue(row[i].c_str());
                }

                this->GetColumnAt(i)->AddRow(*cell);
            }

        }
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_TABLE_CPP