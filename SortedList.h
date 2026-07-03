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
        ConstIterator begin() const{ return ConstIterator(head); };
        ConstIterator end() const{ return ConstIterator(nullptr); };

        SortedList() : head(nullptr), size(0){}
        ~SortedList(){
            while(head){
                Node* curr = head->next;
                delete head;
                head = curr;
            }
        }
        SortedList(const SortedList& other) : head(nullptr), size(other.size){
            Node* tail = nullptr;
            for(Node* curr = other.head; curr; curr = curr->next){
                Node* newNode = new Node{curr->data};
                if (!head) {
                    head = newNode;
                } else {
                    tail->next = newNode;
                }
                tail = newNode;
            }
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
            this->head = nullptr; Node* tail = nullptr;
            for(Node* curr = other.head; curr; curr = curr->next){
                Node* newNode = new Node{curr->data};
                if (!this->head) this->head = newNode; else tail->next = newNode;
                tail = newNode;
            }
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

        void remove(const ConstIterator& it){
            Node* curr = this->head;
            Node* prev = nullptr;
            while(curr){
                if(!(ConstIterator(curr) != it)){
                    // if !(!=), then it is ==, so we found the right one
                    if(prev){
                        prev->next = curr->next;
                    } else{ // prev == nullptr --> one element or less
                        this->head = curr->next;
                    }
                    delete curr;
                    this->size--;
                    return;
                }
                prev = curr;
                curr = curr->next;
            }
        }

        int length() const{
            return size;
        }

        template <typename Condition>
        SortedList filter(Condition pred) const{
            SortedList list;
            Node* tail = nullptr;
            for(Node* curr = head; curr; curr = curr->next) {
                if(pred(curr->data)) {
                    Node* newNode = new Node{curr->data};
                    if (!list.head) list.head = newNode; else tail->next = newNode;
                    tail = newNode; list.size++;
                }
            }
            return list;
        }

        template <class Op>
        SortedList apply(Op op) const{
            SortedList list;
            Node* curr = head;
            while(curr){
                list.insert(op(curr->data));
                curr = curr->next;
            }
            return list;
        }
    };

    template <class T>
    class SortedList<T>::ConstIterator {
    private:
        Node* current;

    public:
        ConstIterator(Node* node = nullptr) : current(node){}
        ConstIterator(const ConstIterator& it) = default;
        ConstIterator& operator=(const ConstIterator& other) = default;
        ~ConstIterator() = default;

        const T& operator*() const{
            return current->data;
        }
        ConstIterator& operator++(){
            if(current == nullptr){
                throw std::out_of_range("End of list");
            }
            current = current->next;
            return *this;
        }
        bool operator!=(const ConstIterator& other) const{
            return this->current != other.current;
        }

    };
}

