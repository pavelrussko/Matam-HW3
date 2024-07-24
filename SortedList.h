#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template<typename T>
    class SortedList {
    private:
        struct Node {
            T data;
            Node *next;

            explicit Node(const T &data = T(), Node *next = nullptr) : data(
                    data), next(next) {}
        };

        Node *Head;
        int size;
    public:
        class ConstIterator;

        SortedList() : Head(new Node), size(0) {
            Head->next = nullptr;
        }

        ~SortedList();

        void Remove(ConstIterator);

        SortedList &operator=(const SortedList &list);

        int length() {
            return size;
        }


        ConstIterator begin() const {
            return ConstIterator(this, &Head);
        }

        ConstIterator end() const {
            Node current = Head;
            for (int i = 0; i < size; ++i) {
                current = current.next;
            }
            return ConstIterator(this, &current);
        }
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list. V
         * 2. copy constructor  - pasha
         * 3. operator= - assignment operator V
         * 4. ~SortedList() - destructor - V
         *
         * iterator:
         * 5. class ConstIterator; V
         * 6. begin method V
         * 7. end method V
         *
         * functions:
         * 8. insert - inserts a new element to the list - pasha
         * 9. remove - removes an element from the list - ofek
         * 10. length - returns the number of elements in the list V
         * 11. filter - returns a new list with elements that satisfy a given condition - friendship
         * 12. apply - returns a new list with elements that were modified by an operation - friendship
         */

    };

    template<class T>
    class SortedList<T>::ConstIterator {
        const SortedList<T> *list;
        Node *current_node;

        ConstIterator(const SortedList<T> *list, Node *current) :
                list(list),
                current_node(current) {}

        ~ConstIterator() = default;

        friend class SortedList<T>;

    public:
        ConstIterator &operator++() {
            if (current_node->next == nullptr) {}
            //throw exc
            current_node = current_node->next;
            return *this;
        }

        ConstIterator &operator=(const ConstIterator &Iterator) = default;
        ConstIterator(const ConstIterator &Iterator) = default;

        bool operator!=(const ConstIterator &Iterator) {
            return !(*this == Iterator);
        }

        const T &operator*() const {
            return current_node->data;
        }

        bool operator==(const ConstIterator &Iterator) {
            return (current_node == Iterator.current_node);
        }
        /**
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. a ctor(or ctors) your implementation needs V
         * 2. copy constructor V
         * 3. operator= - assignment operator V
         * 4. ~ConstIterator() - destructor V
         *
         * operators:
         * 5. operator* - returns the element the iterator points to V
         * 6. operator++ - advances the iterator to the next element V
         * 7. operator!= - returns true if the iterator points to a different element V
         *
         */
    };

    template<class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList &list) {
        if (this == &list) {
            return *this;
        }

        // Clear current list
        while (Head != nullptr) {
            Node *temp = Head;
            Head = Head->next;
            delete temp;
        }
        size = 0;

        for (SortedList<T>::ConstIterator it = list.begin();
             it != list.end(); ++it) {
            insert(*it);
        }

        return *this;
    }

    template<class T>
    SortedList<T>::~SortedList() {
        while (Head != nullptr) {
            Node *temp = Head;
            Head = Head->next;
            delete temp;
        }
    }

    template<class T>
    void SortedList<T>::Remove(ConstIterator iterator) {
        if (Head == nullptr || iterator.current_node == nullptr) {
            //error handling
        }

        if (Head == iterator.current_node) {
            Node *temp = Head;
            Head = Head->next;
            delete temp;
            size--;
        }

        Node *current = Head;
        while (current->next != nullptr &&
               current->next != iterator.current_node) {
            current = current->next;
        }

        if (current->next == iterator.current_node) {
            Node *temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
        }
    }
}