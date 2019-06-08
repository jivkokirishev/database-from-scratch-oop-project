//
// Created by jivko on 27.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_INTEGER_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_INTEGER_H

#include "../abstracts/Type.cpp"

namespace db_components {
    namespace implementation {

        class Integer : public abstract::Type {
        private:
            int value;
            bool is_null;

            void Copy(Integer const &integer);

        public:
            Integer();

            Integer(int value);

            Integer(char const *value);

            Integer(Integer const &integer);

            Integer &operator=(Integer const &integer);

            void SetIsNullTrue();

            bool GetIsNull() const;

            void SetValue(int value);

            void SetValue(char const *value);

            char const *GetValue() const;

            enums::ColumnType GetType() const;
        };
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_INTEGER_H
