//
// Created by jivko on 26.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_COLUMNTYPE_CPP
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_COLUMNTYPE_CPP

#include <map>
#include <string>

namespace db_components {
    namespace enums {

        enum ColumnType {
            integerNumber = 0,
            realNumber = 1,
            string = 2
        };

        struct ColumnTypeConverter {
        public:
            const std::map<std::string, ColumnType> STRING_TO_TYPE = {
                    std::make_pair("integer", integerNumber),
                    std::make_pair("real", realNumber),
                    std::make_pair("string", enums::string)
            };

            const std::map<ColumnType, std::string> TYPE_TO_STRING = {
                    std::make_pair(integerNumber, "integer"),
                    std::make_pair(realNumber, "real"),
                    std::make_pair(enums::string, "string")
            };

        };

    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_COLUMNTYPE_CPP