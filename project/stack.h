// Stack.h
#pragma once
#include <stdexcept>

template <typename T>
class Stack {
private:
    // One box in the chain: holds a value and points to the box below it
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n) : data(d), next(n) {}
    };

    Node* topNode;   // points to the newest item (nullptr when empty)
    int count;       // number of items

public:
    Stack() : topNode(nullptr), count(0) {}

    // Free every node so no memory leaks
    ~Stack() {
        while (!isEmpty())
            pop();
    }

    // Copying is forbidden: two stacks would share the same nodes and crash
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    // Add a value on top: O(1)
    void push(const T& value) {
        Node* n = new Node(value, topNode);
        topNode = n;
        count++;
    }

    // Remove and return the top value: O(1)
    T pop() {
        if (isEmpty())
            throw std::runtime_error("Stack empty");
        Node* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;
        delete temp;
        count--;
        return value;
    }

    // Look at the top value without removing it: O(1)
    const T& peek() const {
        if (isEmpty())
            throw std::runtime_error("Stack empty");
        return topNode->data;
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};