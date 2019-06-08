//
// Created by jivko on 19.05.19.
//

#include "StringColumn.h"
#include "Integer.h"
#include "String.h"


namespace db_components {
    namespace implementation {

        void StringColumn::AddRow(abstract::Type const &value) {
            if (value.GetType() == this->type) {
                String const &tmpValue = dynamic_cast<const String &>(value);

                this->column.push_back(tmpValue);
            }
        }

        void StringColumn::EditRow(abstract::Type const &value, int index) {
            if (value.GetType() == this->type) {
                String const &tmpValue = dynamic_cast<const String &>(value);

                this->column[index] = tmpValue;
            }
        }

        void StringColumn::DeleteRow(int index) {
            this->column.erase(column.begin() + index);
        }

        abstract::Type const &StringColumn::GetRow(int index) const {
            abstract::Type const &value = this->GetElementAt(index);

            return value;
        }

        void StringColumn::Copy(StringColumn const &column) {
            Column::Copy(column);
            this->column = column.column;
        }

        void StringColumn::Erase() {
            Column::Erase();
            this->column.clear();
        }

        StringColumn &StringColumn::operator=(StringColumn const &column) {
            if (this != &column) {
                Erase();
                Copy(column);
            }
            return *this;
        }

        StringColumn::StringColumn(StringColumn const &column) {
            this->Copy(column);
        }

        StringColumn::StringColumn(char const *name) {
            this->type = enums::string;
            this->SetName(name);
            this->column = std::vector<String>();

        }

        StringColumn::~StringColumn() {
            this->Erase();
        }

        implementation::String const &StringColumn::GetElementAt(int index) const {
            return this->column[index];
        }

        int StringColumn::ElementCount() const {
            return this->column.size();
        }
    }
}