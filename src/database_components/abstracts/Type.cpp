//
// Created by jivko on 27.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_Type_CPP
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_Type_CPP

#include <cstring>
#include <iostream>
#include "../enums/ColumnType.cpp"

namespace db_components {
    namespace abstract {

        class Type {
        protected:
            Type() {};

        public:
            virtual ~Type() {};

            Type(Type const &type) = delete;

            virtual Type &operator=(Type const &type) {};

            //virtual bool operator==(Type const &type) const = 0;

            bool operator==(Type const &element) const {
                if (this->GetIsNull() && element.GetIsNull()) {
                    return true;
                }

                char *thisValue = new char[std::strlen(this->GetValue())];
                std::strcpy(thisValue, this->GetValue());

                char *elementValue = new char[std::strlen(element.GetValue())];
                std::strcpy(elementValue, element.GetValue());

                if (std::strcmp(thisValue, elementValue) == 0) {
                    return true;
                }

                delete[] thisValue;
                delete[] elementValue;

                return false;
            }


            virtual void SetIsNullTrue() = 0;

            virtual bool GetIsNull() const = 0;

            virtual void SetValue(char const *value) = 0;

            virtual char const *GetValue() const = 0;

            virtual enums::ColumnType GetType() const = 0;
        };
    }
}
#endif