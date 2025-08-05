#pragma once
#include "Node.h"
#include <functional>
#include <cstddef>

template <typename T>
class LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;  // Nuevo puntero al final de la lista
    size_t count = 0;

public:
    ~LinkedList() { clear(); }
    
    void insert(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        
        if (tail == nullptr) {
            // Lista vacía: cabeza y cola apuntan al nuevo nodo
            head = tail = new_node;
        } else {
            // Insertar al final y actualizar la cola
            tail->next = new_node;
            tail = new_node;
        }
        count++;
    }
    
    bool remove(const T& value) {
        Node<T>* current = head;
        Node<T>* prev = nullptr;
        
        while (current != nullptr) {
            if (current->data == value) {
                // Caso 1: Eliminar la cabeza
                if (prev == nullptr) {
                    head = current->next;
                    // Si era el único nodo, actualizar tail
                    if (head == nullptr) {
                        tail = nullptr;
                    }
                } 
                // Caso 2: Eliminar nodo intermedio o final
                else {
                    prev->next = current->next;
                    // Si era el último nodo, actualizar tail
                    if (current->next == nullptr) {
                        tail = prev;
                    }
                }
                
                delete current;
                count--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }
    
    bool contains(const T& value) const {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }
    
    void forEach(std::function<void(const T&)> func) const {
        Node<T>* current = head;
        while (current) {
            func(current->data);
            current = current->next;
        }
    }
    
    size_t size() const { return count; }
    
    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;  // Resetear el puntero tail
        count = 0;
    }
};