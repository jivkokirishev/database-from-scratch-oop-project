//
// Created by jivko on 23.05.19.
//


#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_OPERATIONTYPE_CPP
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_OPERATIONTYPE_CPP

#include <map>
#include <string>

namespace db_manager {
    namespace enums {

        enum OperationType {
            sum,
            product,
            maximum,
            minimum
        };

        struct OperationTypeConverter {
        public:
            const std::map<std::string, OperationType> STRING_TO_TYPE = {
                    std::make_pair("sum", sum),
                    std::make_pair("product", product),
                    std::make_pair("maximum", maximum),
                    std::make_pair("minimum", minimum)
            };

        };
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_OPERATIONTYPE_CPP