#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
    private:
        struct Node{
            T data;
            Node* next = nullptr;
        };

        Node* head;
        int size;

        public:
        class ConstIterator;
        ConstIterator begin() const;
        ConstIterator end() const;

        SortedList() : head(nullptr), size(0){}
        ~SortedList(){
            while(head){
                Node* curr = head->next;
                delete head;
                head = curr;
            }
        }
        SortedList(const SortedList& other) : head(nullptr), size(other.size){
            Node dummy;
            Node* tail = &dummy;
            for(Node* curr = other.head; curr; (curr = curr->next)){
                tail->next = new Node{curr->data};
                tail = tail->next;
            }
            head = dummy.next;
        }

        SortedList& operator=(const SortedList& other){
            if(this == &other){
                return *this;
            }

            Node* curr = this->head;
            while(curr){
                curr = curr->next;
                delete this->head;
                this->head = curr;
            }
            Node dummy;
            Node* tail = &dummy;
            for(Node* curr = other.head; curr; curr = curr->next){
                tail->next = new Node{curr->data};
                tail = tail->next;
            }
            this->head = dummy.next;
            this->size = other.size;

            return *this;
        }

        void insert(T element){
            Node* newNode = new Node{element};
            if(head == nullptr || element > head->data){
                newNode->next = head;
                head = newNode;
                size++;
                return;
            }
            Node* curr = head->next;
            Node* prev = head;
            while(curr && !(element > curr->data)) {
                prev = curr;
                curr = curr->next;
            }
            prev->next = newNode;
            newNode->next = curr;
            size++;
        }

        void remove(SortedList<T>::ConstIterator it){

        }

        int length(){
            return size;
        }
        /**
         *
         * the class should support the following public interface:
         * if needed, use =default / =delete
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
    private:
        Node* current;

    public:
        ConstIterator(Node* node = nullptr) : current(node){}
        ConstIterator(const ConstIterator& it){

        }
    };


    /**
     * the class should support the following public interface:
     * if needed, use =default / =delete
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
}

