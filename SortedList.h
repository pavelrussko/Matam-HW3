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
        SortedList();
        int length();
        void insert(T&);
        class ConstIterator;
        ~SortedList();
        void Remove(ConstIterator);
        SortedList &operator=(const SortedList &list);

        ConstIterator begin() const;
        ConstIterator end() const;

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
        ConstIterator(const SortedList<T>*, Node*);
        ~ConstIterator() = default;
        friend class SortedList<T>;

    public:
        ConstIterator &operator++();
        ConstIterator &operator=(const ConstIterator &Iterator) = default;
        ConstIterator(const ConstIterator &Iterator) = default;
        bool operator!=(const ConstIterator&);
        const T& operator*() const;
        bool operator==(const ConstIterator&);

    };

    //SortedList implementation
    template<class T>
    SortedList<T>::SortedList() : Head(new Node), size(0) {
        Head->next = nullptr;
    }
    template<class T>
    int SortedList<T>::length() {
        return size;
    }
    template<class T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        return ConstIterator(this, &Head);
    }
    template<class T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        Node current = Head;
        for (int i = 0; i < size; ++i) {
            current = current.next;
        }
        return ConstIterator(this, &current);
    }
    template<class T>
    void SortedList<T>::insert(T& element){
        if(size == 0){
            Head->data = element;
        }
        else if(element >= Head->data){
            Node current = new Node(element, Head);
            Head = current;
        }
        else {
            Node current = new Node(element);

            SortedList<T>::ConstIterator it = begin();
            while (it.current_node->next > element || it.current_node->next == nullptr) {
                it++;
            }
            current.next = it.current_node.next;
            it.current_node->next = current;
            size++;
        }
    }
    template<class T>
    void SortedList<T>::Remove(SortedList::ConstIterator iterator) {
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
    template<class T>
    SortedList<T>::~SortedList() {
        while (Head != nullptr) {
            Node *temp = Head;
            Head = Head->next;
            delete temp;
        }
    }


    //Iterator implementation
    template<class T>
    SortedList<T>::ConstIterator::ConstIterator(const SortedList<T>* list, Node *current) :
            list(list),
            current_node(current) {}
    template<class T>
    typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator++() {
        if (current_node->next == nullptr) {}
        //throw exc
        current_node = current_node->next;
        return *this;
    }
    template<class T>
    bool SortedList<T>::ConstIterator::operator!=(const ConstIterator &Iterator) {
        return !(*this == Iterator);
    }
    template<class T>
    const T& SortedList<T>::ConstIterator::operator*() const {
        return current_node->data;
    }
    template<class T>
    bool SortedList<T>::ConstIterator::operator==(const ConstIterator &Iterator) {
        return (current_node == Iterator.current_node);
    }
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

}