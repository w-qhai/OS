#pragma once

#include "constants.h"

template<typename T>
class List
{
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    Node* head;
    Node* tail;
    uint32_t length;

public:
    List(/* args */);
    ~List();
    void insert(const T& data, int pos);
    void remove(int pos);
};

template<typename T>
List<T>::List(/* args */) {
    head = nullptr;
    tail = nullptr;
}

template<typename T>
void List<T>::insert(const T& data, int pos) {

    Node* p = this->head;
    while (pos--) {
        p = p->next;
    }
    
}

template<typename T>
List<T>::~List() {

}
