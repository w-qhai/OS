#pragma once

#include "constants.h"
#include <cstdint>

template<typename T>
struct Node {
    T data;
    bool use = false;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;
};

template<typename T, int N>
class List {
private:
    Node<T>     _pool[N];
    int         _length;    
    Node<T>*    _head;
    Node<T>*    _tail;

public:
    List() {
        _length = 0;
        _head   = new_node();
        _tail   = new_node();
        _head->next = _tail;
        _tail->prev = _head;
    }

    ~ List() {

    }

    void insert(int i, const T& data) {
        Node<T>* now = _head;

        i = min(i, _length);
        while (i--) {
            now = now->next;
        }

        Node<T>* tmp = new_node();
        tmp->data = data;
        tmp->next = now->next;
        tmp->prev = now;

        now->next->prev = tmp;
        now->next = tmp;
        _length++;

    }

    void append(const T& data) {
        insert(N+1, data);
    }

    void remove(int i) {
        Node<T>* now = _head->next;

        i = min(i, _length);
        while (i--) {
            now = now->next;
        }

        Node<T>* tmp = now;
        now->prev->next = tmp->next;
        now->next->prev = tmp->prev;
        _length--;
    }

    T& at(int i) {
        Node<T>* now = _head->next;

        i = min(i, _length);
        while (i--) {
            now = now->next;
        }

        return now->data;
    }

    uint32_t size() {
        return _length;
    }

    // 第i个数据之后，第一个遇到的data
    T* next(T* data, int i) {
        Node<T>* now = _head->next;

        i = min(i, _length);
        while (i--) {
            now = now->next;
        }

        while (now->data == data) {
            return now->next;
        }

        return nullptr;
    }

    // 第i个数据之前，第一个遇到的
    T* prev(T* data, int i) {
        Node<T>* now = _tail->prev;

        i = min(i, _length);
        while (i--) {
            now = now->prev;
        }

        while (now->data == data) {
            return now->prev;
        }

        return nullptr;
    }

private:
    Node<T>* new_node() {
        for (int i = 0; i < N; i++) {
            if (_pool[i].use == false) {
                _pool[i].use = true;
                return _pool + i;
            }
        }
        return nullptr;
    }

    void del_node(Node<T>* node) {
        node->use = false;
    }
};
