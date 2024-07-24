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
        };
        Node *Head;
        int size;
    public:
        SortedList();
        int length();
        void insert(T&);

        class ConstIterator;
        ConstIterator begin() const;
        ConstIterator end() const;

        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
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


}


