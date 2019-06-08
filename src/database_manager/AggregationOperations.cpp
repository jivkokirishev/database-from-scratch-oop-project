//
// Created by jivko on 23.05.19.
//

#include "AggregationOperations.h"

namespace db_manager {
    double
    AggregationOperations::ExecuteOperation(std::vector<double> selectedValues, enums::OperationType operType) {

        double result = 0;

        switch (operType) {
            case enums::sum: {
                result = 0;

                for (double elem : selectedValues) {
                    result += elem;
                }
            }
                break;
            case enums::product: {
                result = 1;

                for (double elem : selectedValues) {
                    result *= elem;
                }
            }
                break;
            case enums::minimum: {
                result = selectedValues[0];

                for (double elem : selectedValues) {
                    if (result > elem)
                        result = elem;
                }
            }
                break;
            case enums::maximum: {
                result = selectedValues[0];

                for (double elem : selectedValues) {
                    if (result < elem)
                        result = elem;
                }
            }
                break;
        }

        return result;
    }
}