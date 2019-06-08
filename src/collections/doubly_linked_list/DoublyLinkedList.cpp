//
// Created by jivko on 25.04.19.
//

#ifndef DATABASE_FROM_SCRATCH_OOP_PROJECT_DOUBLYLINKEDLIST_CPP
#define DATABASE_FROM_SCRATCH_OOP_PROJECT_DOUBLYLINKEDLIST_CPP

#include "../Collection.cpp"

namespace list {
    template<typename T>
    struct Node {
        T *data;
        Node *next;
        Node *previous;

        ~Node() {
            delete data;
        }
    };

    template<typename T>
    class DoublyLinkedList : public collection::Collection<T> {

        Node<T> *top;
        Node<T> *bottom;
        int element_count;

        void Copy(DoublyLinkedList const &linked_list);

        void Erase();

        Node<T> *GoToNode(int index);

        bool IsNodeAtIndexInList(int index) const;

    public:
        DoublyLinkedList();

        DoublyLinkedList(DoublyLinkedList const &linked_list);

        DoublyLinkedList &operator=(DoublyLinkedList const &linked_list);

        bool IsEmpty() const;

        void Add(T *element);

        void EditAt(int index, T &element);

        void RemoveAt(int index);

        T *ElementAt(int index);

        int GetElementCount() const;

        ~DoublyLinkedList();
    };

    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList(): top(nullptr), bottom(nullptr), element_count(0) {
    }

    template<typename T>
    bool DoublyLinkedList<T>::IsEmpty() const {
        return top == 0 && bottom == 0;
    }

    template<typename T>
    void DoublyLinkedList<T>::Add(T *element) {
        if (!IsEmpty()) {
            Node<T> *tmp = new Node<T>;


            tmp->previous = bottom;
            tmp->data = element;
            tmp->next = nullptr;

            bottom->next = tmp;

            bottom = tmp;
        } else {
            Node<T> *tmp = new Node<T>;


            tmp->previous = nullptr;
            tmp->data = element;
            tmp->next = nullptr;

            top = tmp;
            bottom = tmp;
        }

        element_count += 1;
    }

    template<typename T>
    void DoublyLinkedList<T>::Copy(DoublyLinkedList<T> const &linked_list) {
        top = nullptr;
        bottom = nullptr;
        element_count = linked_list.element_count;

        Node<T> *topNode = linked_list.top;

        while (topNode != nullptr) {
            this->Add(topNode->data);
            topNode = topNode->next;
        }
    }

    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T> const &linked_list) {
        Copy(linked_list);
    }

    template<typename T>
    void DoublyLinkedList<T>::Erase() {
        while (!IsEmpty()) {
            RemoveAt(0);
        }
    }

    template<typename T>
    DoublyLinkedList<T>::~DoublyLinkedList() {
        Erase();
    }

    template<typename T>
    DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(DoublyLinkedList<T> const &linked_list) {
        if (this != &linked_list) {
            Erase();
            Copy(linked_list);
        }
        return *this;
    }

    template<typename T>
    void DoublyLinkedList<T>::EditAt(int index, T &element) {
        Node<T> *nodeAtIndex = GoToNode(index);

        delete nodeAtIndex->data;

        nodeAtIndex->data = &element;
    }

    template<typename T>
    int DoublyLinkedList<T>::GetElementCount() const {
        return element_count;
    }

    template<typename T>
    Node<T> *DoublyLinkedList<T>::GoToNode(int index) {
        if (!IsNodeAtIndexInList(index)) {
            // TODO: Throw an exception!
            return nullptr;
        }

        Node<T> *currentNode = top;
        for (int i = 0; i < index; i++) {
            currentNode = top->next;
        }

        return currentNode;
    }

    template<typename T>
    void DoublyLinkedList<T>::RemoveAt(int index) {

        if (!IsNodeAtIndexInList(index)) {
            // TODO: Throw an exception!
            return;
        }

        Node<T> *nodeAtIndex = GoToNode(index);

        Node<T> *nextNode = nodeAtIndex->next;
        Node<T> *previousNode = nodeAtIndex->previous;

        if (nextNode != 0) {
            nextNode->previous = previousNode;
        }
        if (previousNode != 0) {
            previousNode->next = nextNode;
        }
        if (nextNode == 0 && previousNode == 0) {
            top = nullptr;
            bottom = nullptr;
        }

        element_count -= 1;

        delete nodeAtIndex;
    }

    template<typename T>
    bool DoublyLinkedList<T>::IsNodeAtIndexInList(int index) const {
        return GetElementCount() > index;
    }

    template<typename T>
    T *DoublyLinkedList<T>::ElementAt(int index) {
        Node<T> *nodeAtIndex = GoToNode(index);

        T *result = nodeAtIndex->data;

        return result;
    }
}

#endif //DATABASE_FROM_SCRATCH_OOP_PROJECT