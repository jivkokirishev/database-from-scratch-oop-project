//
// Created by jivko on 27.04.19.
//

#include "Real.h"

#include <string>
#include <cstdlib>

namespace db_components {
    namespace implementation {

        void Real::SetIsNullTrue() {
            this->is_null = true;
        }

        bool Real::GetIsNull() const {
            return this->is_null;
        }

        void Real::SetValue(double value) {
            this->is_null = false;
            this->value = value;
        }

        Real::Real() : value(0), is_null(true) {

        }


        Real::Real(double value) : value(value), is_null(false) {

        }

        Real::Real(const Real &real) {
            Copy(real);
        }

        Real &Real::operator=(Real const &real) {
            if (this != &real) {
                Copy(real);
            }
            return *this;
        }

        void Real::Copy(Real const &real) {
            value = real.value;
            is_null = real.GetIsNull();
        }

        Real::Real(char const *value) : is_null(false) {
            SetValue(value);
        }

        void Real::SetValue(char const *value) {
            double parsedValue = std::atof(value);
            SetValue(parsedValue);
        }

        char const *Real::GetValue() const {
            if (this->GetIsNull()) {
                return "NULL";
            }

            std::string stringValue = std::to_string(value);
            char const *parsedValue = stringValue.c_str();

            return parsedValue;
        }

        enums::ColumnType Real::GetType() const {
            return enums::realNumber;
        }
    }
}