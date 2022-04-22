#pragma once

#include <cstdint>
#include "../lib/constants.h"

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

        i = max(0, i);
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

    int count(const T& data) {
        int res = 0;
        for (Node<T>* now = _head->next; now != nullptr; now = now->next) {
            if (data == now->data) {
                res++;
            }
        }
        return res;
    }

    void remove(int i) {
        Node<T>* now = _head->next;

        i = max(0, i);
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

        i = max(0, i);
        i = min(i, _length);
        while (i--) {
            now = now->next;
        }

        return now->data;
    }

    uint32_t size() {
        return _length;
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
