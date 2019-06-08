//
// Created by jivko on 03.06.19.
//

#include "ConsoleLauncher.h"
#include "CommandParser.h"

namespace ux_components {

    ConsoleLauncher::ConsoleLauncher(db_components::implementation::Database &db) {
        this->dbStreamManager = new db_manager::implementation::DbStreamManager(db, std::cout);
        this->fileManager = new db_manager::implementation::DbFileManager(db, std::cout);

        tableNamesToFilePaths = std::map<std::string, std::string>();
    }

    void ConsoleLauncher::CommandExecutor(std::vector<std::string> &command) {
        try {
            if (command[0] == "open") {
                if (command.size() - 1 != 1) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                this->fileManager->Load(command[1]);

            } else if (command[0] == "save") {
                if (command.size() - 1 != 1) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                if (tableNamesToFilePaths.count(command[1]) != 1) {
                    std::cout
                            << "No such table had been loaded. If you want to save it, please use the saveas function.\n";
                    return;
                }

                this->fileManager->Save(command[1], tableNamesToFilePaths.at(command[1]));

            } else if (command[0] == "saveas") {
                if (command.size() - 1 != 2) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                this->fileManager->Save(command[1], command[2]);

            } else if (command[0] == "close") {
                if (command.size() - 1 != 1) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                this->fileManager->Close(command[1]);

            } else if (command[0] == "showtables") {
                if (command.size() - 1 != 0) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }
                this->dbStreamManager->ShowTables();

            } else if (command[0] == "describe") {
                if (command.size() - 1 != 1) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }
                this->dbStreamManager->Describe(command[1]);

            } else if (command[0] == "print") {
                if (command.size() - 1 != 1) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }
                this->dbStreamManager->Print(command[1]);

            } else if (command[0] == "select") {
                if (command.size() - 1 != 3) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                int columnIndex;
                try {
                    columnIndex = std::stoi(command[3]);

                } catch (std::invalid_argument) {
                    std::cout << "The columnIndex argument you have entered is not an integer number.\n";
                    return;
                }

                this->dbStreamManager->Select(command[1], command[2], columnIndex);

            } else if (command[0] == "addcolumn") {
                if (command.size() - 1 != 3) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                db_components::enums::ColumnType columnType;
                try {
                    auto converter = db_components::enums::ColumnTypeConverter();
                    columnType = converter.STRING_TO_TYPE.at(command[3]);

                } catch (std::out_of_range) {
                    std::cout << "The columnType argument you have entered in does not exist.\n";
                    return;
                }

                this->dbStreamManager->AddColumn(command[1], command[2], columnType);

            } else if (command[0] == "update") {
                if (command.size() - 1 != 5) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                int searchColIndex;
                try {
                    searchColIndex = std::stoi(command[2]);

                } catch (std::invalid_argument) {
                    std::cout << "The searchColumnIndex argument you have entered is not an integer number.\n";
                    return;
                }

                int targetColIndex;
                try {
                    targetColIndex = std::stoi(command[4]);

                } catch (std::invalid_argument) {
                    std::cout << "The targetColumnIndex argument you have entered is not an integer number.\n";
                    return;
                }

                this->dbStreamManager->Update(command[1], searchColIndex, command[3], targetColIndex, command[5]);

            } else if (command[0] == "delete") {
                if (command.size() - 1 != 3) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                int searchColIndex;
                try {
                    searchColIndex = std::stoi(command[2]);

                } catch (std::invalid_argument) {
                    std::cout << "The searchColumnIndex argument you have entered is not an integer number.\n";
                    return;
                }
                this->dbStreamManager->Delete(command[1], searchColIndex, command[3]);

            } else if (command[0] == "insert") {
                if (command.size() - 1 != 1) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                std::string tableName = command[1];
                command.erase(command.begin(), command.begin() + 2);

                this->dbStreamManager->Insert(tableName, command);

            } else if (command[0] == "innerjoin") {
                if (command.size() - 1 != 4) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                int firstColIndex;
                try {
                    firstColIndex = std::stoi(command[2]);

                } catch (std::invalid_argument) {
                    std::cout << "The firstColumnIndex argument you have entered is not an integer number.\n";
                    return;
                }

                int secondColIndex;
                try {
                    secondColIndex = std::stoi(command[4]);

                } catch (std::invalid_argument) {
                    std::cout << "The secondColumnIndex argument you have entered is not an integer number.\n";
                    return;
                }

                this->dbStreamManager->InnerJoin(command[1], firstColIndex, command[3], secondColIndex);

            } else if (command[0] == "rename") {
                if (command.size() - 1 != 2) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                this->dbStreamManager->Rename(command[1], command[2]);

            } else if (command[0] == "count") {
                if (command.size() - 1 != 3) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                int searchColIndex;
                try {
                    searchColIndex = std::stoi(command[2]);

                } catch (std::invalid_argument) {
                    std::cout << "The searchColumnIndex argument you have entered is not an integer number.\n";
                    return;
                }
                this->dbStreamManager->Count(command[1], searchColIndex, command[3]);

            } else if (command[0] == "aggregate") {
                if (command.size() - 1 != 5) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                int searchColIndex;
                try {
                    searchColIndex = std::stoi(command[2]);

                } catch (std::invalid_argument) {
                    std::cout << "The searchColumnIndex argument you have entered is not an integer number.\n";
                    return;
                }

                int targetColIndex;
                try {
                    targetColIndex = std::stoi(command[4]);

                } catch (std::invalid_argument) {
                    std::cout << "The targetColumnIndex argument you have entered is not an integer number.\n";
                    return;
                }

                db_manager::enums::OperationType operationType;

                try {
                    db_manager::enums::OperationTypeConverter converter;
                    operationType = converter.STRING_TO_TYPE.at(command[5]);
                } catch (std::out_of_range) {
                    std::cout << "No such operation can aggregate the table!\n";
                    return;
                }

                this->dbStreamManager->Aggregate(command[1], searchColIndex, command[3], targetColIndex, operationType);

            } else if (command[0] == "clear") {
                if (command.size() - 1 != 0) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

                std::cout << "This functionality has not been supported yet!\n";

            } else if (command[0] == "exit") {
                if (command.size() - 1 != 0) {
                    std::cout << "Command arguments does NOT math the parameter count of the function " << command[0]
                              << "!\n";
                    return;
                }

            } else {
                std::cout << "There is no such command, please try again!\n";
            }

        } catch (std::exception &e) {
            std::cout
                    << "An unknown problem with the database occurred! Please check if your last command is correct. "
                    << "If you think that there is a bug in the system, please contact with the developer: "
                    << "jivkokirishev@gmail.com/n";

            std::cout << "More info about the exception: "
                      << e.what();
        }
    }

    void ConsoleLauncher::Run() {

        std::cout << "Squirrel database v0.3 has started:\n";

        std::vector<std::string> command;
        do {
            std::string commandLine;
            std::getline(std::cin, commandLine);

            // Keep reading a new line while there is
            // a blank line
            while (commandLine.length() == 0) {
                std::getline(std::cin, commandLine);
            }

            command.clear();

            try {
                CommandParser::Split(commandLine, command);

            } catch (std::invalid_argument &e) {
                std::cout << e.what();
                return;
            }
            this->CommandExecutor(command);

        } while (command[0] != "exit");

        std::cout << "Bye!\n";
    }

    ConsoleLauncher::~ConsoleLauncher() {
        //delete dbStreamManager;
        //delete fileManager;
    }
}