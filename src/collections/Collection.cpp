//
// Created by jivko on 24.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_COLLECTION_CPP
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_COLLECTION_CPP

namespace collection {

    template<typename T>
    class Collection {
    private:
        Collection();

    public:
        virtual ~Collection();

        Collection(Collection const &) = delete;

        Collection &operator=(Collection const &) = delete;

        virtual void Add(T const& element) = 0;

        virtual void EditAt(int index, T const& element) = 0;

        virtual void RemoveAt(int index) = 0;

        virtual T &operator[](int index) const = 0;

        virtual int GetElementCount() const = 0;
    };
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT_COLLECTION_CPP
