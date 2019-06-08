//
// Created by jivko on 29.05.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_DBFILEMANAGER_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_DBFILEMANAGER_H

#include "../database_components/implementations/Database.h"


namespace db_manager {
    namespace implementation {

        class DbFileManager {
        private:
            std::ostream &os;
            db_components::implementation::Database &database;

            void SplitString(std::string &line, std::vector<std::string> &container,
                             const std::string &delim = "");

        public:
            DbFileManager(db_components::implementation::Database &database, std::ostream &os);

            std::string Load(std::string const &fileName);

            void Save(std::string const &tableName, std::string const &fileName);

            void Close(std::string const &tableName);
        };
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_DBFILEMANAGER_H
