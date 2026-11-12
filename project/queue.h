// Queue.h
#pragma once
#include <stdexcept>

template <typename T>
class Queue {
private:
    // One box in the chain: holds a value and points to the next box
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* frontNode;   // remove from here (oldest item)
    Node* rearNode;    // add here (newest item)
    int count;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    // Free every node so no memory leaks
    ~Queue() {
        while (!isEmpty())
            dequeue();
    }

    // Copying is forbidden (same reason as Stack)
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    // Add a value at the back: O(1)
    void enqueue(const T& value) {
        Node* n = new Node(value);
        if (isEmpty()) {
            frontNode = n;          // first item: both pointers use it
            rearNode = n;
        } else {
            rearNode->next = n;     // link after the current last node
            rearNode = n;           // new node becomes the last
        }
        count++;
    }

    // Remove and return the front value: O(1)
    T dequeue() {
        if (isEmpty())
            throw std::runtime_error("Queue empty");
        Node* temp = frontNode;
        T value = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr)
            rearNode = nullptr;     // queue became empty: reset rear too
        delete temp;
        count--;
        return value;
    }

    // Look at the front value without removing it: O(1)
    const T& front() const {
        if (isEmpty())
            throw std::runtime_error("Queue empty");
        return frontNode->data;
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};