//
// Created by jivko on 26.04.19.
//

#include "Integer.h"

#include <string>
#include <cstdlib>

namespace db_components {
    namespace implementation {

        void Integer::SetIsNullTrue() {
            this->is_null = true;
        }

        bool Integer::GetIsNull() const {
            return this->is_null;
        }

        void Integer::SetValue(int value) {
            this->is_null = false;
            this->value = value;
        }

        Integer::Integer() : value(0), is_null(true) {

        }


        Integer::Integer(int value) : value(value), is_null(false) {

        }

        Integer::Integer(const Integer &integer) {
            Copy(integer);
        }

        Integer &Integer::operator=(Integer const &integer) {
            if (this != &integer) {
                Copy(integer);
            }
            return *this;
        }

        void Integer::Copy(Integer const &integer) {
            value = integer.value;
            is_null = integer.GetIsNull();
        }

        Integer::Integer(char const *value) : is_null(false) {
            SetValue(value);
        }

        void Integer::SetValue(char const *value) {
            int parsedValue = std::atoi(value);
            SetValue(parsedValue);
        }

        char const *Integer::GetValue() const {
            if (this->GetIsNull()) {
                return "NULL";
            }

            std::string stringValue = std::to_string(value);
            char const *parsedValue = stringValue.c_str();

            return parsedValue;
        }

        enums::ColumnType Integer::GetType() const {
            return enums::integerNumber;
        }
    }
}
