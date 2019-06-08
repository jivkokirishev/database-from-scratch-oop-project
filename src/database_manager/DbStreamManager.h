//
// Created by jivko on 19.05.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_DBSTREAMMANAGER_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_DBSTREAMMANAGER_H

#include <iostream>
#include <string>
#include <vector>

#include "../database_components/abstracts/Type.cpp"
#include "../database_components/implementations/Database.h"
#include "enums/OperationType.cpp"

namespace db_manager {
    namespace implementation {
        class DbStreamManager {
        private:
            std::ostream &os;
            db_components::implementation::Database &database;

            void InteractivePrint(std::vector<std::vector<std::string>> &rows, int rowsPerPage = 10);

            void PagePrint(std::vector<std::vector<std::string>> &rows);

            db_components::abstract::Type *
            StringToTypeConverter(db_components::enums::ColumnType type, std::string const &value);

        public:
            DbStreamManager(db_components::implementation::Database &database, std::ostream &os);

            void ShowTables();

            void Describe(std::string tableName);

            void Print(std::string tableName);

            void Select(std::string const &tableName, db_components::abstract::Type const &value, int columnIndex);

            void Select(std::string const &tableName, std::string const &value, int columnIndex);

            void AddColumn(std::string const &tableName, std::string const &columnName,
                           db_components::enums::ColumnType type);

            void Update(std::string const &tableName,
                        int searchColIndex,
                        db_components::abstract::Type &searchValue,
                        int targetColIndex,
                        db_components::abstract::Type &targetValue);

            void Update(std::string const &tableName,
                        int searchColIndex,
                        std::string const &searchValue,
                        int targetColIndex,
                        std::string const &targetValue);

            void Delete(std::string const &tableName,
                        int searchColIndex,
                        db_components::abstract::Type const &searchValue);

            void Delete(std::string const &tableName,
                        int searchColIndex,
                        std::string const &searchValue);


            void Insert(std::string const &tableName, std::vector<std::string> const &row);

            std::string InnerJoin(std::string const &fTableName, int fColumnIndex,
                                  std::string const &sTableName, int sColumnIndex);


            void Rename(std::string const &oldTableName, std::string const &newTableName);

            void Count(std::string const &tableName,
                       int searchColIndex,
                       db_components::abstract::Type const &searchValue);

            void Count(std::string const &tableName,
                       int searchColIndex,
                       std::string const &searchValue);

            void Aggregate(std::string const &tableName,
                           int searchColInd,
                           db_components::abstract::Type &searchValue,
                           int targetColInd,
                           enums::OperationType operType);

            void Aggregate(std::string const &tableName,
                           int searchColInd,
                           std::string const &searchValue,
                           int targetColInd,
                           enums::OperationType operType);

            ~DbStreamManager();

        };
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_DBSTREAMMANAGER_H
