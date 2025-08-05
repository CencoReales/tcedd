#pragma once
#include "Node.h"
#include <cstddef>


template <typename T>
class Queue {
    Node<T>* front = nullptr;
    Node<T>* rear = nullptr;
    size_t count = 0;

public:
    ~Queue() { clear(); }
    
    void enqueue(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        
        if (!rear) {
            front = rear = new_node;
        } else {
            rear->next = new_node;
            rear = new_node;
        }
        count++;
    }
    
    T dequeue() {
        if (!front) return T();
        
        Node<T>* temp = front;
        T value = front->data;
        front = front->next;
        
        if (!front) rear = nullptr;
        
        delete temp;
        count--;
        return value;
    }
    
    size_t size() const { return count; }
    
    void clear() {
        while (front) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        count = 0;
    }
};