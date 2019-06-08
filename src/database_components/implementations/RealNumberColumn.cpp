//
// Created by jivko on 19.05.19.
//

#include "RealNumberColumn.h"
#include "Real.h"

namespace db_components {
    namespace implementation {

        RealNumberColumn::RealNumberColumn(char const *name) {
            this->type = enums::realNumber;
            this->SetName(name);
            this->column = std::vector<Real>();
        }

        void RealNumberColumn::Copy(RealNumberColumn const &column) {
            Column::Copy(column);
            this->column = column.column;
        }

        void RealNumberColumn::Erase() {
            Column::Erase();
            this->column.clear();
        }

        RealNumberColumn &RealNumberColumn::operator=(RealNumberColumn const &column) {
            if (this != &column) {
                Erase();
                Copy(column);
            }
            return *this;
        }

        RealNumberColumn::RealNumberColumn(RealNumberColumn const &column) {
            this->Copy(column);
        }

        RealNumberColumn::~RealNumberColumn() {
            this->Erase();
        }

        void RealNumberColumn::AddRow(abstract::Type const &value) {
            if (value.GetType() == this->type) {
                Real const &tmpValue = dynamic_cast<const Real &>(value);

                this->column.push_back(tmpValue);
            }
        }

        void RealNumberColumn::EditRow(abstract::Type const &value, int index) {
            if (value.GetType() == this->type) {
                Real const &tmpValue = dynamic_cast<const Real &>(value);

                this->column[index] = tmpValue;
            }
        }

        void RealNumberColumn::DeleteRow(int index) {
            this->column.erase(column.begin() + index);
        }

        abstract::Type const &RealNumberColumn::GetRow(int index) const {
            abstract::Type const &value = this->GetElementAt(index);

            return value;
        }

        Real const &RealNumberColumn::GetElementAt(int index) const {
            return this->column[index];
        }

        int RealNumberColumn::ElementCount() const {
            return this->column.size();
        }
    }
}
