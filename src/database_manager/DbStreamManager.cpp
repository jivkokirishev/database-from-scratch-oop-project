//
// Created by jivko on 19.05.19.
//

#include "DbStreamManager.h"

#include "../database_components/implementations/Integer.h"
#include "../database_components/implementations/Real.h"
#include "../database_components/implementations/String.h"
#include "AggregationOperations.h"

#include <fstream>
#include <cstring>

namespace db_manager {
    namespace implementation {
        DbStreamManager::DbStreamManager(db_components::implementation::Database &database,
                                         std::ostream &os) : database(database), os(os) {

        }

        void DbStreamManager::ShowTables() {
            this->os << "----------------Tables----------------\n";

            for (int i = 0; i < this->database.TableCount(); i++) {
                os << this->database.GetTableAt(i).GetName() << std::endl;
            }

            os << "Total Count: " << this->database.TableCount() << std::endl;
        }

        void DbStreamManager::Describe(std::string tableName) {

            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            os << "---------------- Columns Of " << tableName << " Table ----------------\n";

            auto typeConverter = db_components::enums::ColumnTypeConverter();

            for (int i = 0; i < table.ColumnCount(); i++) {
                os << table.GetColumnAt(i)->GetName() << "  --->  ";
                os << typeConverter.TYPE_TO_STRING.at(table.GetColumnAt(i)->GetType()) << std::endl;
            }
            os << "Total Count: " << table.ColumnCount() << std::endl;
        }

        void DbStreamManager::Print(std::string tableName) {

            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            auto rows = std::vector<std::vector<std::string>>();

            for (int i = 0; i < table.GetColumnAt(0)->ElementCount(); ++i) {

                auto row = std::vector<std::string>();
                for (int j = 0; j < table.ColumnCount(); ++j) {

                    char *tmpCell = new char[std::strlen(table.GetColumnAt(j)->GetRow(i).GetValue())];
                    std::strcpy(tmpCell, table.GetColumnAt(j)->GetRow(i).GetValue());

                    std::string cell = tmpCell;

                    delete[] tmpCell;

                    row.push_back(cell);
                }

                rows.push_back(row);
            }

            this->InteractivePrint(rows);
        }

        void DbStreamManager::InteractivePrint(std::vector<std::vector<std::string>> &rows, int rowsPerPage) {

            int numberOfPages = rows.size() / rowsPerPage;
            if (rows.size() % rowsPerPage != 0) {
                numberOfPages++;
            }

            int button;
            int currentPage = 1;
            do {

                auto packetOfRows = std::vector<std::vector<std::string>>();

                int startRowIndex = rowsPerPage * (currentPage - 1);
                int rowCounter = 0;
                while (rowCounter < rowsPerPage && rowCounter + startRowIndex < rows.size()) {

                    packetOfRows.push_back(rows[startRowIndex + rowCounter]);
                    rowCounter++;
                }

                this->PagePrint(packetOfRows);

                os << "This is " << currentPage << " of " << numberOfPages
                   << " pages with rows. Choose one of the options:\n";
                os << "1 - go to the next page\n";
                os << "-1 - go to the previous page\n";
                os << "0 - exit\n";

                std::cin >> button;

                switch (button) {
                    case 1: {
                        if (currentPage < numberOfPages) {
                            currentPage++;
                        } else {
                            os << "There are no more pages!\n";
                            return;
                        }
                    }
                        break;
                    case -1: {
                        if (currentPage > 1) {
                            currentPage--;
                        } else {
                            os << "You are at the first page!\n";
                            return;
                        }
                    }
                }
            } while (button != 0);
        }

        void DbStreamManager::PagePrint(std::vector<std::vector<std::string>> &rows) {

            for (int i = 0; i < rows.size(); i++) {
                for (int j = 0; j < rows[i].size(); ++j) {
                    os << rows[i][j] << " ";
                }

                os << std::endl;
            }
        }

        void DbStreamManager::Select(std::string const &tableName, db_components::abstract::Type const &value,
                                     int columnIndex) {

            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            db_components::abstract::Column *column;

            try {
                column = table.GetColumnAt(columnIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from columnIndex argument in the select functionality."
                        << e.what() << std::endl;

                return;
            }


            std::vector<std::vector<std::string>> selectedRows = std::vector<std::vector<std::string>>();


            for (int i = 0; i < column->ElementCount(); ++i) {
                if (value == column->GetRow(i)) {

                    auto row = std::vector<std::string>();
                    for (int j = 0; j < table.ColumnCount(); ++j) {
                        std::string cell = table.GetColumnAt(j)->GetRow(i).GetValue();
                        row.push_back(cell);
                    }

                    selectedRows.push_back(row);
                }
            }

            this->InteractivePrint(selectedRows);
        }

        void DbStreamManager::Select(std::string const &tableName, std::string const &value, int columnIndex) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            db_components::abstract::Column *column;

            try {
                column = table.GetColumnAt(columnIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from columnIndex argument in the select functionality."
                        << e.what() << std::endl;

                return;
            }

            db_components::abstract::Type *cell = this->StringToTypeConverter(column->GetType(), value);

            this->Select(tableName, *cell, columnIndex);

            delete cell;
        }

        void DbStreamManager::AddColumn(std::string const &tableName, std::string const &columnName,
                                        db_components::enums::ColumnType type) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            table.AddColumn(type, columnName);

            db_components::abstract::Type *cell = this->StringToTypeConverter(type, "NULL");

            for (int i = 0; i < table.GetColumnAt(0)->ElementCount(); ++i) {
                db_components::abstract::Type *tmpCell = cell;
                table.GetColumnAt(table.ColumnCount() - 1)->AddRow(*tmpCell);
            }

            delete cell;
        }

        void DbStreamManager::Update(std::string const &tableName, int searchColIndex,
                                     db_components::abstract::Type &searchValue,
                                     int targetColIndex, db_components::abstract::Type &targetValue) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            db_components::abstract::Column *searchCol;
            try {
                searchCol = table.GetColumnAt(searchColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from searchColIndex argument in the update functionality."
                        << e.what() << std::endl;

                return;
            }

            db_components::abstract::Column *targetCol;
            try {
                targetCol = table.GetColumnAt(targetColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from targetColIndex argument in the update functionality."
                        << e.what() << std::endl;

                return;
            }

            for (int i = 0; i < searchCol->ElementCount(); ++i) {
                if (searchCol->GetRow(i) == searchValue) {
                    targetCol->EditRow(targetValue, i);
                }
            }
        }

        void DbStreamManager::Update(std::string const &tableName, int searchColIndex, std::string const &searchValue,
                                     int targetColIndex, std::string const &targetValue) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            db_components::abstract::Column *searchCol;

            try {
                searchCol = table.GetColumnAt(searchColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from searchColIndex argument in the update functionality."
                        << e.what() << std::endl;

                return;
            }
            db_components::abstract::Type *searchCell = this->StringToTypeConverter(searchCol->GetType(), searchValue);


            db_components::abstract::Column *targetCol;

            try {
                targetCol = table.GetColumnAt(targetColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from targetColIndex argument in the update functionality."
                        << e.what() << std::endl;

                return;
            }
            db_components::abstract::Type *targetCell = this->StringToTypeConverter(targetCol->GetType(), searchValue);


            this->Update(tableName, searchColIndex, *searchCell, targetColIndex, *targetCell);

            delete searchCell;
            delete targetCell;
        }

        void DbStreamManager::Delete(std::string const &tableName, int searchColIndex,
                                     db_components::abstract::Type const &searchValue) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);


            db_components::abstract::Column *searchCol;

            try {
                searchCol = table.GetColumnAt(searchColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from searchColIndex argument in the delete functionality."
                        << e.what() << std::endl;

                return;
            }

            // TODO: recreate the cycle
            for (int i = 0; i < searchCol->ElementCount(); ++i) {
                if (searchCol->GetRow(i) == searchValue) {
                    for (int j = 0; j < table.ColumnCount(); ++j) {
                        table.GetColumnAt(j)->DeleteRow(i);
                    }
                    i--;
                }
            }
        }

        void DbStreamManager::Delete(std::string const &tableName, int searchColIndex, std::string const &searchValue) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            db_components::abstract::Column *searchCol;

            try {
                searchCol = table.GetColumnAt(searchColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from searchColIndex argument in the delete functionality."
                        << e.what() << std::endl;

                return;
            }
            db_components::abstract::Type *searchCell = this->StringToTypeConverter(searchCol->GetType(), searchValue);

            this->Delete(tableName, searchColIndex, *searchCell);

            delete searchCell;
        }

        void DbStreamManager::Insert(std::string const &tableName, std::vector<std::string> const &row) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            if (table.ColumnCount() != row.size()) {
                os << "Row arguments input count does not math table column count!\n";
                return;
            }

            table.InsertRow(row);
        }

        std::string
        DbStreamManager::InnerJoin(std::string const &fTableName, int fColumnIndex,
                                   std::string const &sTableName, int sColumnIndex) {

            if (!this->database.TableExist(fTableName) || !this->database.TableExist(sTableName)) {
                os << "Invalid Table Name!\n";
                return "";

            }

            std::string newTableName = fTableName + "_" + sTableName + "_" +
                                       std::to_string(fColumnIndex) + "_" + std::to_string(sColumnIndex);

            this->database.AddTable(newTableName);
            db_components::implementation::Table &newTable = this->database.GetTableByName(newTableName);

            db_components::implementation::Table &firstTable = this->database.GetTableByName("people");
            for (int i = 0; i < firstTable.ColumnCount(); ++i) {
                newTable.AddColumn(firstTable.GetColumnAt(i)->GetType(),
                                   fTableName + "_" + firstTable.GetColumnAt(i)->GetName());
            }

            db_components::implementation::Table &secondTable = this->database.GetTableByName(sTableName);
            for (int i = 0; i < secondTable.ColumnCount(); ++i) {
                newTable.AddColumn(secondTable.GetColumnAt(i)->GetType(),
                                   sTableName + "_" + secondTable.GetColumnAt(i)->GetName());
            }

            for (int i = 0; i < firstTable.GetColumnAt(fColumnIndex)->ElementCount(); ++i) {

                for (int j = 0; j < secondTable.GetColumnAt(sColumnIndex)->ElementCount(); ++j) {

                    if (firstTable.GetColumnAt(fColumnIndex)->GetRow(i) ==
                        secondTable.GetColumnAt(sColumnIndex)->GetRow(j)) {

                        for (int k = 0; k < firstTable.ColumnCount(); ++k) {

                            db_components::abstract::Type const &tmpCell = firstTable.GetColumnAt(k)->GetRow(i);

                            newTable.GetColumnAt(k)->AddRow(tmpCell);
                        }

                        for (int k = 0; k < secondTable.ColumnCount(); ++k) {

                            db_components::abstract::Type const &tmpCell = secondTable.GetColumnAt(k)->GetRow(j);

                            newTable.GetColumnAt(firstTable.ColumnCount() + k)->AddRow(tmpCell);
                        }
                    }
                }
            }

            return newTableName;
        }

        void DbStreamManager::Rename(std::string const &oldTableName, std::string const &newTableName) {

            if (!this->database.TableExist(oldTableName)) {
                os << "Invalid Table Name!\n";
                return;

            } else if (this->database.TableExist(newTableName)) {
                os << "New Table Name Is Not Unique!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(oldTableName);

            table.SetName(newTableName);
        }

        void
        DbStreamManager::Count(std::string const &tableName, int searchColIndex,
                               db_components::abstract::Type const &searchValue) {

            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            db_components::abstract::Column *searchCol;

            try {
                searchCol = table.GetColumnAt(searchColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from searchColIndex argument in the count functionality."
                        << e.what() << std::endl;

                return;
            }

            int rowCounter = 0;
            for (int i = 0; i < searchCol->ElementCount(); ++i) {
                if (searchCol->GetRow(i) == searchValue) {
                    rowCounter++;
                }
            }

            os << "Total Count Of Rows With " << table.GetColumnAt(searchColIndex)->GetName()
               << " Value " << searchValue.GetValue() << ": "
               << rowCounter << std::endl;
        }

        void
        DbStreamManager::Count(std::string const &tableName, int searchColIndex, std::string const &searchValue) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            db_components::abstract::Column *searchCol;

            try {
                searchCol = table.GetColumnAt(searchColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from searchColIndex argument in the count functionality."
                        << e.what() << std::endl;

                return;
            }
            db_components::abstract::Type *searchCell = this->StringToTypeConverter(searchCol->GetType(), searchValue);

            this->Count(tableName, searchColIndex, *searchCell);

            delete searchCell;
        }

        void DbStreamManager::Aggregate(std::string const &tableName, int searchColIndex,
                                        db_components::abstract::Type &searchValue, int targetColIndex,
                                        enums::OperationType operType) {

            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            db_components::abstract::Column *searchColumn;
            try {
                searchColumn = table.GetColumnAt(searchColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from searchColIndex argument in the aggregate functionality."
                        << e.what() << std::endl;

                return;
            }

            db_components::abstract::Column *targetColumn;
            try {
                targetColumn = table.GetColumnAt(targetColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from targetColIndex argument in the aggregate functionality."
                        << e.what() << std::endl;

                return;
            }

            if (targetColumn->GetType() == db_components::enums::string) {
                os << "Invalid Target Column Type! It should be integer or real.\n";
                return;
            }

            auto selectedCells = std::vector<double>();


            for (int i = 0; i < searchColumn->ElementCount(); ++i) {
                if (searchValue == searchColumn->GetRow(i)) {

                    std::string strCellValue = targetColumn->GetRow(i).GetValue();

                    double cellValue;

                    if (strCellValue == "NULL") {
                        cellValue = 0;
                    } else {
                        cellValue = std::stod(strCellValue);
                    }

                    selectedCells.push_back(cellValue);
                }
            }

            double result = AggregationOperations::ExecuteOperation(selectedCells, operType);

            os << "The result of the operation is: " << result << std::endl;
        }


        void
        DbStreamManager::Aggregate(std::string const &tableName, int searchColIndex, std::string const &searchValue,
                                   int targetColIndex, enums::OperationType operType) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }
            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            db_components::abstract::Column *searchColumn;
            try {
                searchColumn = table.GetColumnAt(searchColIndex);
            } catch (std::out_of_range &e) {
                os
                        << "Out of range exception was fired while getting column from searchColIndex argument in the aggregate functionality."
                        << e.what() << std::endl;

                return;
            }
            db_components::abstract::Type *searchCell = this->StringToTypeConverter(searchColumn->GetType(),
                                                                                    searchValue);

            this->Aggregate(tableName, searchColIndex, *searchCell, targetColIndex, operType);

            delete searchCell;
        }

        DbStreamManager::~DbStreamManager() {
        }

        db_components::abstract::Type *
        DbStreamManager::StringToTypeConverter(db_components::enums::ColumnType type, std::string const &value) {
            db_components::abstract::Type *cell;

            switch (type) {
                case db_components::enums::integerNumber : {
                    cell = new db_components::implementation::Integer();
                }
                case db_components::enums::realNumber : {
                    cell = new db_components::implementation::Real();
                }
                case db_components::enums::string : {
                    cell = new db_components::implementation::String();
                }
            }

            if (value == "NULL") {
                cell->SetIsNullTrue();
            } else {
                cell->SetValue(value.c_str());
            }

            return cell;
        }
    }
}