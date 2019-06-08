//
// Created by jivko on 27.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_REAL_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_REAL_H

#include "../abstracts/Type.cpp"

namespace db_components {
    namespace implementation {

        class Real : public abstract::Type {
        private:
            double value;
            bool is_null;

            void Copy(Real const &real);

        public:
            Real();

            Real(double value);

            Real(char const *value);

            Real(Real const &real);

            Real &operator=(Real const &real);

            void SetIsNullTrue();

            bool GetIsNull() const;

            void SetValue(double value);

            void SetValue(char const *value);

            char const *GetValue() const;

            enums::ColumnType GetType() const;
        };
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_REAL_H
