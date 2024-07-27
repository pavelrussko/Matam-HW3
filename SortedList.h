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

            Node(const T &data, Node *next = nullptr) : data(data),
                                                        next(next) {}

            bool operator==(const Node &node);
        };

        Node *Head;
        int size;
    public:
        template<class Condition>
        SortedList filter(Condition c) const;

        template<class Reshape>
        SortedList apply(Reshape r) const;

        SortedList();
        SortedList(const SortedList<T> &);
        int length() const;
        void insert(const T &);

        class ConstIterator;

        ~SortedList();
        void remove(ConstIterator);
        SortedList &operator=(const SortedList &list);

        ConstIterator begin() const;
        ConstIterator end() const;

        /**
         *
         * the class should support the following public interface:
         * if needed, use =default / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list. V
         * 2. copy constructor  - V
         * 3. operator= - assignment operator V
         * 4. ~SortedList() - destructor - V
         *
         * iterator:
         * 5. class ConstIterator; V
         * 6. begin method V
         * 7. end method V
         *
         * functions:
         * 8. insert - inserts a new element to the list - V
         * 9. remove - removes an element from the list - V
         * 10. length - returns the number of elements in the list V
         * 11. filter - returns a new list with elements that satisfy a given condition - V
         * 12. apply - returns a new list with elements that were modified by an operation - V
         */

    };

    template<typename T>
    bool SortedList<T>::Node::operator==(const Node &node) {
        return data == node.data;
    }

    template<class T>
    class SortedList<T>::ConstIterator {
        const SortedList<T> *list;
        Node *current_node;
        ConstIterator(const SortedList<T> *, Node *);

        friend class SortedList<T>;

    public:
        ~ConstIterator() = default;
        ConstIterator &operator++();
        ConstIterator &operator=(const ConstIterator &Iterator) = default;
        ConstIterator(const ConstIterator &Iterator) = default;
        bool operator!=(const ConstIterator &);
        const T &operator*() const;
        bool operator==(const ConstIterator &);

    };


    //SortedList implementation
    template<class T>
    SortedList<T>::SortedList() : Head(nullptr), size(0) {}

    template<class T>
    SortedList<T>::SortedList(const SortedList<T> &list) : Head(nullptr),
                                                           size(0) {
        for (ConstIterator it = list.begin(); it != list.end(); ++it) {
            this->insert(*it);
        }
    }

    template<class T>
    int SortedList<T>::length() const {
        return size;
    }

    template<class T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        return ConstIterator(this, Head);
    }

    template<class T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        return ConstIterator(this, nullptr);
    }

    template<class T>
    void SortedList<T>::insert(const T &element) {
        Node *newNode = new Node(element);
        if (Head == nullptr || element > Head->data) {
            newNode->next = Head;
            Head = newNode;
        } else {
            Node *current = Head;
            while (current->next != nullptr && current->next->data > element) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    template<class T>
    void SortedList<T>::remove(SortedList::ConstIterator iterator) {
        if (Head == nullptr) {
            return;
        }

        if (iterator.current_node == nullptr) {
            return;
        }

        if (Head == iterator.current_node) {
            Node *temp = Head;
            Head = Head->next;
            delete temp;
            size--;
            return;
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

    template<class T>
    template<class Condition>
    SortedList<T> SortedList<T>::filter(Condition c) const {
        SortedList filtered;
        for (ConstIterator it = begin(); it != end(); ++it) {
            if (c(*it)) {
                filtered.insert(*it);
            }
        }
        return filtered;
    }

    template<class T>
    template<class Reshape>
    SortedList<T> SortedList<T>::apply(Reshape r) const {
        SortedList reshaped;
        for (ConstIterator it = begin(); it != end(); ++it) {
            reshaped.insert(r(*it));
        }
        return reshaped;
    }

    template<class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList &list) {
        if (this == &list) {
            return *this;
        }

        while (Head != nullptr) {
            Node *temp = Head;
            Head = Head->next;
            delete temp;
        }
        size = 0;

        for (ConstIterator it = list.begin(); it != list.end(); ++it) {
            insert(*it);
        }

        return *this;
    }

    //Iterator implementation
    template<class T>
    SortedList<T>::ConstIterator::ConstIterator(const SortedList<T> *list,
                                                Node *current)
            : list(list), current_node(current) {}

    template<class T>
    typename SortedList<T>::ConstIterator &
    SortedList<T>::ConstIterator::operator++() {
        if (current_node == nullptr) {
            throw std::out_of_range(
                    "Iterator cannot be incremented past the end.");
        }
        current_node = current_node->next;
        return *this;
    }

    template<class T>
    bool
    SortedList<T>::ConstIterator::operator!=(const ConstIterator &Iterator) {
        return !(*this == Iterator);
    }

    template<class T>
    const T &SortedList<T>::ConstIterator::operator*() const {
        return current_node->data;
    }

    template<class T>
    bool
    SortedList<T>::ConstIterator::operator==(const ConstIterator &Iterator) {
        return current_node == Iterator.current_node;
    }

}