//
// Created by jivko on 03.06.19.
//

#include <stdexcept>
#include <cstring>
#include "CommandParser.h"

namespace ux_components {

    void CommandParser::Split(std::string line, std::vector<std::string> &splittedCommand) {

        std::vector<std::size_t> spaceIndexes;

        std::size_t symbolIndex = 0;
        symbolIndex = line.find(" ", 0);

        while (symbolIndex != std::string::npos) {

            spaceIndexes.push_back(symbolIndex);
            symbolIndex = line.find(" ", symbolIndex + 1);
        }

        if (spaceIndexes.empty()) {
            RemoveExtraSymbols(splittedCommand);
            splittedCommand.clear();
            splittedCommand.push_back(line);
            return;
        }

        std::vector<std::size_t> quoteIndexes;

        symbolIndex = line.find("\"", 0);
        while (symbolIndex != std::string::npos) {

            int escapeCounter = 0;

            while (symbolIndex - escapeCounter - 1 > 0 && line[symbolIndex - escapeCounter - 1] == '\\') {
                escapeCounter++;
            }

            if (escapeCounter % 2 == 0) {
                quoteIndexes.push_back(symbolIndex);
            }
            symbolIndex = line.find("\"", symbolIndex + 1);
        }

        if (quoteIndexes.size() % 2 != 0) {
            throw std::invalid_argument("Quotation symbols have to be even count. The input is invalid!\n");
        }


        std::vector<std::size_t> splitIndexes;
        if (!quoteIndexes.empty()) {
            int i = 0;
            int j = 0;
            while (i < spaceIndexes.size() && j < quoteIndexes.size()) {
                if (j == 0) {
                    if (spaceIndexes[i] < quoteIndexes[j]) {

                        splitIndexes.push_back(spaceIndexes[i]);
                        i++;
                    } else {
                        j++;
                    }

                } else {
                    while (quoteIndexes[j] > spaceIndexes[i] && i < spaceIndexes.size()) {
                        i++;
                    }

                    if (quoteIndexes[j] < spaceIndexes[i] && j + 1 < quoteIndexes.size() &&
                        spaceIndexes[i] < quoteIndexes[j + 1]) {

                        splitIndexes.push_back(spaceIndexes[i]);
                        i++;
                    } else {
                        j += 2;
                    }
                }
            }

            while (i < spaceIndexes.size()) {
                if (quoteIndexes[quoteIndexes.size() - 1] < spaceIndexes[i]) {

                    splitIndexes.push_back(spaceIndexes[i]);
                    i++;
                }
            }
        } else {
            splitIndexes = spaceIndexes;
        }

        splittedCommand.clear();
        splittedCommand.push_back(line.substr(0, splitIndexes[0]));

        int i = 0;
        while (i < splitIndexes.size() - 1) {
            splittedCommand.push_back(line.substr(splitIndexes[i] + 1, splitIndexes[i + 1] - splitIndexes[i] - 1));
            i++;
        }
        splittedCommand.push_back(line.substr(splitIndexes[i] + 1));

        RemoveExtraSymbols(splittedCommand);
    }

    void CommandParser::RemoveExtraSymbols(std::vector<std::string> &splittedCommand) {

        for (int i = 0; i < splittedCommand.size(); ++i) {

            std::string &argument = splittedCommand[i];

            std::size_t symbolIndex = 0;

            symbolIndex = argument.find_first_of("\\\"", 0);
            while (symbolIndex != std::string::npos) {

                char tmpChar = argument[symbolIndex];

                if (tmpChar == '\"') {
                    argument.erase(symbolIndex, 1);
                    symbolIndex = argument.find_first_of("\\\"", symbolIndex);
                } else if (tmpChar == '\\') {
                    argument.erase(symbolIndex, 1);
                    symbolIndex = argument.find_first_of("\\\"", symbolIndex + 1);
                }

            }

            argument.erase(argument.find_last_not_of(" \n\r\t") + 1);
            argument.erase(0, argument.find_first_not_of(" \n\r\t"));
        }
    }
}