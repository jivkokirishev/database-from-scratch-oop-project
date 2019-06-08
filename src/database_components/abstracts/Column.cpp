//
// Created by jivko on 26.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_COLUMN_CPP
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_COLUMN_CPP


#include "Column.h"

#include <cstring>

namespace db_components {
    namespace abstract {
        Column::Column() : name(nullptr) {

        }

        char const *Column::GetName() const {
            const int NAME_LENGTH = strlen(name);
            char *return_string = new char[NAME_LENGTH + 1];
            strcpy(return_string, name);

            return return_string;
        }

        void Column::SetName(char const *name) {
            delete[] this->name;
            const int NAME_LENGTH = strlen(name);
            this->name = new char[NAME_LENGTH + 1];
            strcpy(this->name, name);
        }

        Column &Column::operator=(Column const &column) {
            if (this != &column) {
                Erase();
                Copy(column);
            }
            return *this;
        }

        void Column::Copy(Column const &column) {
            this->type = column.GetType();
            SetName(column.name);
        }

        void Column::Erase() {
            delete[] name;
            name = nullptr;
        }

        enums::ColumnType Column::GetType() const {
            return this->type;
        }
    }
}
#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_COLUMN_CPP
