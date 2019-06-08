//
// Created by jivko on 23.05.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_AGGREGATIONOPERATIONS_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_AGGREGATIONOPERATIONS_H

#include <vector>
#include "enums/OperationType.cpp"

namespace db_manager {
    class AggregationOperations {
    public:
        static double ExecuteOperation(std::vector<double> selectedValues, enums::OperationType operType);
    };
}


#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_AGGREGATIONOPERATIONS_H
