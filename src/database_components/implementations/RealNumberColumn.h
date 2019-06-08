//
// Created by jivko on 19.05.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_REALNUMBERCOLUMN_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_REALNUMBERCOLUMN_H

#include "../../collections/Collection.cpp"
#include "../../collections/doubly_linked_list/DoublyLinkedList.cpp"

#include "../abstracts/Column.h"
#include "Real.h"

#include <vector>
#include <string>

namespace db_components {
    namespace implementation {

        class RealNumberColumn : public abstract::Column {
        private:
            std::vector<Real> column;

        protected:
            void Copy(RealNumberColumn const &column);

            void Erase();

        public:

            RealNumberColumn(char const *name);

            RealNumberColumn(RealNumberColumn const &column);

            RealNumberColumn &operator=(RealNumberColumn const &column);

            void AddRow(abstract::Type const &value);

            void EditRow(abstract::Type const &value, int index);

            void DeleteRow(int index);

            Real const &GetElementAt(int index) const;

            abstract::Type const &GetRow(int index) const;

            int ElementCount() const;

            ~RealNumberColumn();
        };

    }
}
#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_REALNUMBERCOLUMN_H
