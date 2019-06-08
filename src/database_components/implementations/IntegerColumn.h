//
// Created by jivko on 19.05.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_INTEGERCOLUMN_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_INTEGERCOLUMN_H

#include "../../collections/Collection.cpp"
#include "../../collections/doubly_linked_list/DoublyLinkedList.cpp"
#include "../abstracts/Type.cpp"
#include "Integer.h"
#include "../abstracts/Column.h"

#include <vector>
#include <string>

namespace db_components {
    namespace implementation {

        class IntegerColumn : public abstract::Column {
        private:
            std::vector<Integer> column;

        protected:
            void Copy(IntegerColumn const &column);

            void Erase();

        public:

            IntegerColumn(char const *name);

            IntegerColumn(IntegerColumn const &column);

            IntegerColumn &operator=(IntegerColumn const &column);

            void AddRow(abstract::Type const &value);

            void EditRow(abstract::Type const &value, int index);

            void DeleteRow(int index);

            Integer const &GetElementAt(int index) const;

            abstract::Type const &GetRow(int index) const;

            int ElementCount() const;

            ~IntegerColumn();
        };

    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_INTEGERCOLUMN_H
