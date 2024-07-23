#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
    private:
        struct Node{
            T data;
            Node* next;
        };
        Node* Head;
        int size;
    public:
        SortedList(): Head(new Node), size(0){
            Head->next = nullptr;
        }
        int length(){
            return size;
        }




        class ConstIterator;
        ConstIterator begin() const{
            return ConstIterator(this, Head);
        }
        ConstIterator end() const{
            Node current = Head;
            for (int i = 0; i < size; ++i) {
                current = current.next;
            }
            return current;
        }
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

    template <class T>
    class SortedList<T>::ConstIterator {
        const SortedList<T>* list;
        Node current_node;
        ConstIterator(const SortedList<T>* list, Node current):
                list(list),
                current_node(current){}
        ~ConstIterator() = default;
        friend class SortedList<T>;
    public:
        ConstIterator& operator++(){
            if(current_node.next == nullptr){}
            //throw exc
            current_node = current_node.next;
            return *this;
        }
        /**
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. a ctor(or ctors) your implementation needs
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~ConstIterator() - destructor
         *
         * operators:
         * 5. operator* - returns the element the iterator points to
         * 6. operator++ - advances the iterator to the next element
         * 7. operator!= - returns true if the iterator points to a different element
         *
         */
    };
}


