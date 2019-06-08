//
// Created by jivko on 27.04.19.
//

#include <cstring>
#include "String.h"

namespace db_components {
    namespace implementation {
        String::String() : value(nullptr), is_null(true) {

        }

        String::String(char const *value) : value(nullptr), is_null(false) {
            SetValue(value);
        }

        String::String(String const &string) : value(nullptr) {
            Copy(string);
        }

        String &String::operator=(String const &string) {
            if (this != &string) {
                Copy(string);
            }
            return *this;
        }


        void String::Copy(const String &string) {

            if (string.is_null) {
                this->SetIsNullTrue();
            } else {
                SetValue(string.value);
            }
        }

        void String::SetIsNullTrue() {
            this->is_null = true;
        }

        bool String::GetIsNull() const {
            return this->is_null;
        }

        void String::SetValue(char const *value) {
            this->is_null = false;

            delete[] this->value;
            this->value = nullptr;
            const int VALUE_LENGTH = strlen(value);
            this->value = new char[VALUE_LENGTH + 1];
            strcpy(this->value, value);
        }

        char const *String::GetValue() const {
            if (this->GetIsNull()) {
                return "NULL";
            }

            const int VALUE_LENGTH = strlen(value);
            char *return_string = new char[VALUE_LENGTH + 1];
            strcpy(return_string, value);

            return return_string;
        }

        String::~String() {
            delete[] this->value;
            this->value = nullptr;
        }

        enums::ColumnType String::GetType() const {
            return enums::string;
        }
    }
}