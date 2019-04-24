//
// Created by root on 24.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_COLLECTION_H
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_COLLECTION_H

namespace collection {

    template<typename T>
    class Collection {
    private:
        Collection();

    public:
        virtual ~Collection();

        Collection(Collection const &) = delete;

        Collection &operator=(Collection const &) = delete;

        virtual void Add(T element) = 0;

        virtual void InsertAt(int index, T element) = 0;

        virtual void RemoveAt(int index) = 0;

        virtual T &operator[](int index) const = 0;
    };
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_COLLECTION_H
