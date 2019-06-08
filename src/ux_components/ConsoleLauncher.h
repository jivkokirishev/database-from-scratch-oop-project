//
// Created by jivko on 03.06.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_CONSOLELAUNCHER_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_CONSOLELAUNCHER_H

#include "../database_manager/DbStreamManager.h"
#include "../database_manager/DbFileManager.h"

namespace ux_components {

    class ConsoleLauncher {
    private:
        db_manager::implementation::DbStreamManager *dbStreamManager;
        db_manager::implementation::DbFileManager *fileManager;

        std::map<std::string, std::string> tableNamesToFilePaths;

        void CommandExecutor(std::vector<std::string> &command);

    public:
        ConsoleLauncher(db_components::implementation::Database &db);

        void Run();

        ~ConsoleLauncher();
    };
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_CONSOLELAUNCHER_H
