#include <emscripten/bind.h>
#include <vector>
#include <string>
#include "data_structures/LinkedList.h"
#include "data_structures/Stack.h"
#include "data_structures/Queue.h"

namespace em = emscripten;

// Instancias globales con inicialización estática
static LinkedList<char> globalList;
static Stack<char> globalStack;
static Queue<char> globalQueue;

// Operaciones para Lista Enlazada
void listInsert(char value) {
    globalList.insert(value);
}

bool listRemove(char value) {
    return globalList.remove(value);
}

bool listContains(char value) {
    return globalList.contains(value);
}

em::val listGetAll() {
    std::vector<char> elements;
    globalList.forEach([&](char c) { elements.push_back(c); });
    return em::val::array(elements);
}

size_t listSize() {
    return globalList.size();
}

void listClear() {
    globalList.clear();
}

// Operaciones para Pila
void stackPush(char value) {
    globalStack.push(value);
}

char stackPop() {
    if (globalStack.empty()) return '\0';
    return globalStack.pop();
}

em::val stackGetAll() {
    std::vector<char> elements;
    Stack<char> tempStack;
    
    while (!globalStack.empty()) {
        char c = globalStack.pop();
        elements.push_back(c);
        tempStack.push(c);
    }
    
    while (!tempStack.empty()) {
        globalStack.push(tempStack.pop());
    }
    
    return em::val::array(elements);
}

size_t stackSize() {
    return globalStack.size();
}

void stackClear() {
    globalStack.clear();
}

// Operaciones para Cola
void queueEnqueue(char value) {
    globalQueue.enqueue(value);
}

char queueDequeue() {
    if (globalQueue.size() == 0) return '\0';
    return globalQueue.dequeue();
}

em::val queueGetAll() {
    std::vector<char> elements;
    size_t count = globalQueue.size();
    
    for (size_t i = 0; i < count; ++i) {
        char c = globalQueue.dequeue();
        elements.push_back(c);
        globalQueue.enqueue(c);
    }
    
    return em::val::array(elements);
}

size_t queueSize() {
    return globalQueue.size();
}

void queueClear() {
    globalQueue.clear();
}
// Función de diagnóstico
void debugTest() {
    listInsert('D');
    stackPush('S');
    queueEnqueue('Q');
}
// Exponer funciones
EMSCRIPTEN_BINDINGS(module) {
    em::function("listInsert", &listInsert);
    em::function("listRemove", &listRemove);
    em::function("listContains", &listContains);
    em::function("listGetAll", &listGetAll);
    em::function("listSize", &listSize);
    em::function("listClear", &listClear);
    em::function("debugTest", &debugTest);
    
    em::function("stackPush", &stackPush);
    em::function("stackPop", &stackPop);
    em::function("stackGetAll", &stackGetAll);
    em::function("stackSize", &stackSize);
    em::function("stackClear", &stackClear);
    
    em::function("queueEnqueue", &queueEnqueue);
    em::function("queueDequeue", &queueDequeue);
    em::function("queueGetAll", &queueGetAll);
    em::function("queueSize", &queueSize);
    em::function("queueClear", &queueClear);
    
    em::register_vector<char>("vector<char>");
}