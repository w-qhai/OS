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

public:
    List(/* args */);
    ~List();
};

List::List(/* args */) {
    head = nullptr;

}

List::~List() {

}
