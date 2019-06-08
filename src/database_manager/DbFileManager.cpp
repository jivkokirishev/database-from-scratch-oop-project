//
// Created by jivko on 29.05.19.
//

#include <string>
#include <vector>
#include <fstream>
#include "DbFileManager.h"

#include "../database_components/abstracts/Type.cpp"

namespace db_manager {
    namespace implementation {

        DbFileManager::DbFileManager(db_components::implementation::Database &database,
                                     std::ostream &os) : database(database), os(os) {

        }

        std::string DbFileManager::Load(std::string const &fileName) {

            std::ifstream tableFile;
            tableFile.open(fileName);

            std::string line;

            std::string tableName = "";

            if (tableFile.is_open()) {

                std::getline(tableFile, tableName);
                if (!tableFile.eof()) {
                    if (this->database.TableExist(tableName)) {
                        os << "This table already exist. It can NOT be loaded again!\n";

                        tableFile.close();
                        return "";
                    }

                    this->database.AddTable(tableName);
                }

                auto &table = database.GetTableByName(tableName);


                std::getline(tableFile, line);
                if (!tableFile.eof()) {

                    auto container = std::vector<std::string>();
                    this->SplitString(line, container, ",");

                    for (auto elem : container) {
                        auto nameTypePair = std::vector<std::string>();
                        this->SplitString(elem, nameTypePair, "=");

                        if (nameTypePair.size() != 2) {
                            os << "Columns name=type record is NOT correct!\n";

                            database.DeleteTableByName(tableName);

                            tableFile.close();
                            return "";
                        }

                        auto typeConverter = db_components::enums::ColumnTypeConverter();

                        db_components::enums::ColumnType columnType;
                        try {
                            columnType = typeConverter.STRING_TO_TYPE.at(nameTypePair[1]);

                        } catch (std::out_of_range) {
                            os << "The column type argument is NOT correct!\n";
                            return "";
                        }

                        table.AddColumn(columnType, nameTypePair[0]);
                    }
                }


                std::getline(tableFile, line);
                while (!tableFile.eof()) {

                    auto row = std::vector<std::string>();
                    this->SplitString(line, row, ",");

                    if (row.size() != table.ColumnCount()) {
                        os << "Rows in the file are NOT consistent! They have different element count!\n";

                        database.DeleteTableByName(tableName);

                        tableFile.close();
                        return "";
                    } else {
                        table.InsertRow(row);
                    }

                    std::getline(tableFile, line);
                }
            }

            tableFile.close();

            return tableName;
        }

        void DbFileManager::Save(std::string const &tableName, std::string const &fileName) {
            if (!this->database.TableExist(tableName)) {
                os << "Invalid Table Name!\n";
                return;
            }

            db_components::implementation::Table &table = this->database.GetTableByName(tableName);

            std::ofstream tableFile;
            tableFile.open(fileName, std::ios::trunc);

            tableFile << table.GetName() << std::endl;

            std::string separator = "";

            for (int i = 0; i < table.ColumnCount(); ++i) {
                std::string colType;

                auto typeConverter = db_components::enums::ColumnTypeConverter();

                tableFile << separator << table.GetColumnAt(i)->GetName() << "="
                          << typeConverter.TYPE_TO_STRING.at(table.GetColumnAt(i)->GetType());

                separator = ",";
            }
            tableFile << std::endl;

            for (int i = 0; i < table.GetColumnAt(0)->ElementCount(); ++i) {

                std::string separator = "";
                for (int j = 0; j < table.ColumnCount(); ++j) {

                    char *tmpCell = new char[std::strlen(table.GetColumnAt(j)->GetRow(i).GetValue())];
                    std::strcpy(tmpCell, table.GetColumnAt(j)->GetRow(i).GetValue());

                    std::string cell = tmpCell;

                    delete[] tmpCell;

                    std::size_t found = cell.find_first_of(",");
                    while (found != std::string::npos) {
                        int slashCounter = 0;

                        while (found - slashCounter - 1 > 0 && cell[found - slashCounter - 1] == '\\') {
                            slashCounter++;
                        }

                        for (int k = 0; k < slashCounter; ++k) {

                            cell.insert(found - 1, "\\");
                        }

                        cell.insert(found - 1, "\\");
                        found = cell.find_first_of(",", found + slashCounter + 2);
                    }

                    tableFile << separator << cell;

                    separator = ",";

                }
                tableFile << std::endl;
            }

            tableFile.close();
        }

        void DbFileManager::SplitString(std::string &line, std::vector<std::string> &container,
                                        const std::string &delimeter) {
            std::size_t current;
            current = line.find_first_of(delimeter);
            int extraSlashCount = 0;
            while (current != std::string::npos) {

                int escapeCounter = 0;

                while (current - escapeCounter - 1 > 0 && line[current - escapeCounter - 1] == '\\') {
                    escapeCounter++;
                }

                if (escapeCounter % 2 == 0) {

                    if (escapeCounter > 0) {
                        extraSlashCount = (escapeCounter / 2);
                    }

                    container.push_back(line.substr(0, current - extraSlashCount));
                    line.erase(0, current + 1);
                    current = 0;
                } else {
                    if (escapeCounter > 0) {
                        extraSlashCount = (escapeCounter / 2 + 1);
                    }

                    line.erase(current - escapeCounter, extraSlashCount);
                }

                current = line.find_first_of(delimeter, current);
            }

            int escapeCounter = 0;
            while (current - escapeCounter - 1 > 0 && line[current - escapeCounter - 1] == '\\') {
                escapeCounter++;
            }

            if (escapeCounter % 2 == 0) {

                if (escapeCounter > 0) {
                    extraSlashCount = (escapeCounter / 2);
                }

                container.push_back(line.substr(0, current - extraSlashCount));
                line.erase(0, current + 1);
                current = 0;
            } else {
                if (escapeCounter > 0) {
                    extraSlashCount = (escapeCounter / 2 + 1);
                }

                line.erase(current - escapeCounter, extraSlashCount);
            }
        }

        void DbFileManager::Close(std::string const &tableName) {

            if (database.TableExist(tableName)) {
                database.DeleteTableByName(tableName);

            } else {
                os << "Table: " << tableName << "does NOT exist.It can not be closed\\deleted!\n";
            }
        }
    }
}