//
// Created by jivko on 19.05.19.
//


#include "IntegerColumn.h"

namespace db_components {
    namespace implementation {

        IntegerColumn::IntegerColumn(char const *name) {
            this->type = enums::integerNumber;
            this->SetName(name);
            this->column = std::vector<Integer>();
        }

        void IntegerColumn::Copy(IntegerColumn const &column) {
            Column::Copy(column);
            this->column = column.column;
        }

        void IntegerColumn::Erase() {
            Column::Erase();
            this->column.clear();
        }

        IntegerColumn &IntegerColumn::operator=(IntegerColumn const &column) {
            if (this != &column) {
                Erase();
                Copy(column);
            }
            return *this;
        }

        IntegerColumn::IntegerColumn(IntegerColumn const &column) {
            this->Copy(column);
        }

        IntegerColumn::~IntegerColumn() {
            this->Erase();
        }

        void IntegerColumn::AddRow(abstract::Type const &value) {
            if (value.GetType() == this->type) {
                Integer const &tmpValue = dynamic_cast<const Integer &>(value);

                this->column.push_back(tmpValue);
            }
        }

        void IntegerColumn::EditRow(abstract::Type const &value, int index) {
            if (value.GetType() == this->type) {
                Integer const &tmpValue = dynamic_cast<const Integer &>(value);

                this->column[index] = tmpValue;
            }
        }

        void IntegerColumn::DeleteRow(int index) {
            this->column.erase(column.begin() + index);
        }

        Integer const &IntegerColumn::GetElementAt(int index) const {
            return this->column[index];
        }

        abstract::Type const &IntegerColumn::GetRow(int index) const {
            abstract::Type const &value = this->GetElementAt(index);

            return value;
        }

        int IntegerColumn::ElementCount() const {
            return this->column.size();
        }
    }
}
