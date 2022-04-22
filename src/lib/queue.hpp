#pragma once
#include "list.hpp"

template<typename T, int N>
class Queue {
public:
    List<T, N> list;

    T front() {
        return list.at(0);
    }

    void push(const T& data) {
        list.append(data);
    }

    void pop() {
        if (list.size() > 0) {
            list.remove(0);
        }
    }

    void clear() {
        while (list.size()) {
            list.remove(0);
        }
    }

    bool empty() {
        return !list.size();
    }
};

template<typename T, int N>
class CirQueue {
    T _buff[N];
    uint32_t    _front = 0;
    uint32_t    _rear = 0;
    uint32_t    _size = 0;

public:
    void push(const T& value) {
        _buff[_rear] = value;
        _rear = (_rear + 1) % N;
        _size++;
    }

    void pop() {
        _front = (_front + 1) % N;
        _size--;
    }

    void clear() {
        _front = _rear = 0;
    }

    T front() {
        return _buff[_front];
    }

    bool empty() {
        return _rear == _front;
    } 
};