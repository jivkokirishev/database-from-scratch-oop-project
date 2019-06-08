//
// Created by jivko on 03.06.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_COMMANDPARSER_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_COMMANDPARSER_H


#include <vector>
#include <string>

namespace ux_components {

    class CommandParser {
    private:
        static void RemoveExtraSymbols(std::vector<std::string> &splittedCommand);

    public:
        static void Split(std::string line, std::vector<std::string> &splittedCommand);
    };
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_COMMANDPARSER_H
