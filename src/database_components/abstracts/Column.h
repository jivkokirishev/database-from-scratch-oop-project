//
// Created by jivko on 27.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_COLUMN_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_COLUMN_H

#include "../../collections/Collection.cpp"
#include "../../collections/doubly_linked_list/DoublyLinkedList.cpp"
#include "../enums/ColumnType.cpp"
#include "Type.cpp"

#include <string>

namespace db_components {
    namespace abstract {

        class Column {
        private:
            char *name;

        protected:
            enums::ColumnType type;

            virtual void Copy(Column const &column);

            virtual void Erase();

        public:

            Column();

            Column &operator=(Column const &);

            char const *GetName() const;

            void SetName(char const *name);

            virtual void AddRow(abstract::Type const &value) = 0;

            virtual void EditRow(abstract::Type const &value, int index) = 0;

            virtual void DeleteRow(int index) = 0;

            virtual abstract::Type const &GetRow(int index) const = 0;

            virtual enums::ColumnType GetType() const;

            virtual int ElementCount() const = 0;
        };
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_COLUMN_H
