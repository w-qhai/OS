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