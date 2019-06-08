//
// Created by jivko on 19.05.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_STRINGCOLUMN_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_STRINGCOLUMN_H

#include "../../collections/Collection.cpp"
#include "../../collections/doubly_linked_list/DoublyLinkedList.cpp"

#include "../abstracts/Column.h"
#include "String.h"

#include <vector>
#include <string>

namespace db_components {
    namespace implementation {

        class StringColumn : public abstract::Column {
        private:
            std::vector<String> column;

        protected:
            void Copy(StringColumn const &column);

            void Erase();

        public:

            StringColumn(char const *name);

            StringColumn(StringColumn const &column);

            StringColumn &operator=(StringColumn const &column);

            void AddRow(abstract::Type const &value);

            void EditRow(abstract::Type const &value, int index);

            void DeleteRow(int index);

            implementation::String const &GetElementAt(int index) const;

            abstract::Type const &GetRow(int index) const;

            ~StringColumn();

            int ElementCount() const;
        };
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_STRINGCOLUMN_H
