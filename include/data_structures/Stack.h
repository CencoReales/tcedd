#pragma once
#include "Node.h"
#include <cstddef>
#include <cassert>


template <typename T>
class Stack {
    Node<T>* top = nullptr;
    size_t count = 0;

public:
    ~Stack() { clear(); }
    
    void push(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        new_node->next = top;
        top = new_node;
        count++;
    }
    
    T pop() {
        #ifdef DEBUG
        assert(top && "Stack vacío en pop()");
        #endif
        
        if (!top) return T();
        
        Node<T>* temp = top;
        T value = top->data;
        top = top->next;
        delete temp;
        count--;
        return value;
    }
    
    size_t size() const { return count; }
    bool empty() const { return count == 0; }
    
    void clear() {
        while (top) {
            Node<T>* temp = top;
            top = top->next;
            delete temp;
        }
        count = 0;
    }
};