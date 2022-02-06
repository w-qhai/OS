#include "queue.h"

void Queue::push(const uint8_t value) {
    _buff[_rear] = value;
    _rear = (_rear + 1) % 128;
    _size++;
}

void Queue::pop() {
    _front = (_front + 1) % 128;
    _size--;
}

void Queue::clear() {
    _front = _rear = 0;
}

uint8_t Queue::front() {
    return _buff[_front];
}

bool Queue::empty() {
    return _rear == _front;
}