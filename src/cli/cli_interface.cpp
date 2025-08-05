#include "cli/cli_interface.h"
#include "data_structures/LinkedList.h"
#include "data_structures/Stack.h"
#include "data_structures/Queue.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

void CLI::InteractiveMenu::addOption(const string& desc, function<void()> action) {
    options.push_back({desc, action});
}

void CLI::InteractiveMenu::display() const {
    cout << "\n=== " << title << " ===\n";
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i].description << "\n";
    }
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";
}

void CLI::InteractiveMenu::run() {
    int choice;
    do {
        display();
        cin >> choice;
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (choice > 0 && static_cast<size_t>(choice) <= options.size()) {
            options[choice - 1].action();
        } else if (choice != 0) {
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (choice != 0);
}

void CLI::runLinkedListDemo() {
    LinkedList<char> list;
    InteractiveMenu menu("Lista Enlazada");
    
    menu.addOption("Insertar elemento", [&]() {
        char value;
        cout << "Ingrese un carácter: ";
        cin >> value;
        list.insert(value);
        cout << "Elemento insertado.\n";
    });
    
    menu.addOption("Eliminar elemento", [&]() {
        char value;
        cout << "Ingrese carácter a eliminar: ";
        cin >> value;
        if (list.remove(value)) {
            cout << "Elemento eliminado.\n";
        } else {
            cout << "Elemento no encontrado.\n";
        }
    });
    
    menu.addOption("Buscar elemento", [&]() {
        char value;
        cout << "Ingrese carácter a buscar: ";
        cin >> value;
        cout << (list.contains(value) ? "Encontrado" : "No encontrado") << "\n";
    });
    
    menu.addOption("Mostrar elementos", [&]() {
        cout << "Elementos: ";
        list.forEach([](char c) { cout << c << ' '; });
        cout << "\n";
    });
    
    menu.addOption("Tamaño de la lista", [&]() {
        cout << "Tamaño: " << list.size() << "\n";
    });
    
    menu.run();
}

void CLI::runStackDemo() {
    Stack<char> stack;
    InteractiveMenu menu("Pila (LIFO)");
    
    menu.addOption("Push (Apilar)", [&]() {
        char value;
        cout << "Ingrese un carácter: ";
        cin >> value;
        stack.push(value);
        cout << "Elemento apilado.\n";
    });
    
    menu.addOption("Pop (Desapilar)", [&]() {
        if (stack.empty()) {
            cout << "Pila vacía.\n";
        } else {
            char value = stack.pop();
            cout << "Elemento desapilado: " << value << "\n";
        }
    });
    
    menu.addOption("Mostrar tope", [&]() {
        if (stack.empty()) {
            cout << "Pila vacía.\n";
        } else {
            char value = stack.pop();
            stack.push(value);
            cout << "Tope: " << value << "\n";
        }
    });
    
    menu.addOption("Mostrar elementos", [&]() {
        if (stack.empty()) {
            cout << "Pila vacía.\n";
        } else {
            cout << "Elementos (desde el tope): ";
            Stack<char> tempStack;
            while (!stack.empty()) {
                char c = stack.pop();
                cout << c << ' ';
                tempStack.push(c);
            }
            
            while (!tempStack.empty()) {
                stack.push(tempStack.pop());
            }
            cout << "\n";
        }
    });
    
    menu.run();
}

void CLI::runQueueDemo() {
    Queue<char> queue;
    InteractiveMenu menu("Cola (FIFO)");
    
    menu.addOption("Enqueue (Encolar)", [&]() {
        char value;
        cout << "Ingrese un carácter: ";
        cin >> value;
        queue.enqueue(value);
        cout << "Elemento encolado.\n";
    });
    
    menu.addOption("Dequeue (Desencolar)", [&]() {
        if (queue.size() == 0) {
            cout << "Cola vacía.\n";
        } else {
            char value = queue.dequeue();
            cout << "Elemento desencolado: " << value << "\n";
        }
    });
    
    menu.addOption("Mostrar frente", [&]() {
        if (queue.size() == 0) {
            cout << "Cola vacía.\n";
        } else {
            char value = queue.dequeue();
            queue.enqueue(value);
            cout << "Frente: " << value << "\n";
            
            for (size_t i = 1; i < queue.size(); ++i) {
                queue.enqueue(queue.dequeue());
            }
        }
    });
    
    menu.addOption("Mostrar elementos", [&]() {
        if (queue.size() == 0) {
            cout << "Cola vacía.\n";
        } else {
            cout << "Elementos: ";
            size_t count = queue.size();
            for (size_t i = 0; i < count; ++i) {
                char c = queue.dequeue();
                cout << c << ' ';
                queue.enqueue(c);
            }
            cout << "\n";
        }
    });
    
    menu.run();
}

void CLI::runMainMenu() {
    InteractiveMenu menu("Estructuras de Datos Optimizadas");
    
    menu.addOption("Lista Enlazada", []() {
        runLinkedListDemo();
    });
    
    menu.addOption("Pila (LIFO)", []() {
        runStackDemo();
    });
    
    menu.addOption("Cola (FIFO)", []() {
        runQueueDemo();
    });
    
    menu.addOption("Mostrar información del sistema", []() {
        cout << "Sistema optimizado para bajo consumo de recursos\n";
        cout << "Tamaño de nodo: " << sizeof(Node<char>) << " bytes\n";
        cout << "Memoria por elemento: 5 bytes (char + puntero)\n";
    });
    
    menu.run();
}