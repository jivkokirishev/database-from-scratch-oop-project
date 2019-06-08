//
// Created by jivko on 27.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_STRING_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_STRING_H

#include "../abstracts/Type.cpp"

namespace db_components {
    namespace implementation {

        class String : public abstract::Type {
            char *value;
            bool is_null;

            void Copy(String const &string);

        public:
            String();

            String(char const *value);

            String(String const &string);

            String &operator=(String const &string);

            void SetIsNullTrue();

            bool GetIsNull() const;

            void SetValue(char const *value);

            char const *GetValue() const;

            enums::ColumnType GetType() const;

            ~String();
        };
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_STRING_H
