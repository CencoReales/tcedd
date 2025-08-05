TCEDD - Estructuras de Datos Dinámicas en C++ (CLI y WebAssembly)

Implementación modular de estructuras de datos fundamentales —Lista Enlazada, Pila y Cola— utilizando C++17 con plantillas (template <typename T>) y soporte dual para ejecución en consola y navegador.

Este proyecto busca consolidar los conceptos de estructuras dinámicas a través de una arquitectura limpia, moderna y portátil.

---

Características Destacadas

Plantillas genéricas (template) para tipado flexible

Gestión explícita de memoria con punteros crudos

CLI interactivo con menús por estructura

Compilación a WebAssembly vía Emscripten

Código moderno, minimalista y seguro (C++17)

Eliminación completa de memoria (destructores robustos)

Makefile centralizado para construir, servir y limpiar

---

Estructura del Proyecto

tcedd/
├── bin/                     # Ejecutables CLI
├── include/
│   ├── data_structures/     # Código fuente de estructuras
│   │   ├── LinkedList.h
│   │   ├── Queue.h
│   │   ├── Stack.h
│   │   └── Node.h
│   └── cli/
│       └── cli_interface.h
├── src/
│   ├── main.cpp             # Entrada CLI
│   ├── web_main.cpp         # Entrada WebAssembly
│   └── cli/
│       └── cli_interface.cpp
├── web/                     # Archivos generados para Web
├── Makefile
└── README.md


---

Compilación y Ejecución

Requisitos

Compilador C++ compatible con C++17

Emscripten para compilar a WebAssembly

GNU Make

Modo Consola (CLI)

make cli
./bin/data_structures_cli

Modo Web (WebAssembly)

make web
make serve_web

Navega a: http://localhost:8000

Limpieza

make clean

---

Estructuras Implementadas

LinkedList<T>

Inserción eficiente al final

Eliminación por valor

Búsqueda y recorrido

Limpieza segura de memoria


Stack<T>

Apilamiento (push) y desapilamiento (pop)

Consultas de tamaño y estado (empty)

Destrucción sin fugas

Queue<T>

Encolado (enqueue) y desencolado (dequeue)

Seguimiento de tamaño

Liberación total de nodos

---

Interfaz CLI

Sistema de menús jerárquicos con entrada por consola. Permite manipular cada estructura mediante opciones simples y claras:

=== MENÚ PRINCIPAL ===
1. Lista Enlazada
2. Pila
3. Cola
0. Salir
Seleccione una opción:

Cada estructura tiene su propio submenú operativo:

=== Lista Enlazada ===
1. Insertar elemento
2. Eliminar elemento
3. Buscar elemento
4. Mostrar elementos
0. Volver

---

WebAssembly (WASM)

El módulo generado permite integrar las estructuras directamente con interfaces web mediante embind:

EMSCRIPTEN_BINDINGS(module) {
    em::function("listInsert", &listInsert);
    em::function("stackPush", &stackPush);
    em::function("queueEnqueue", &queueEnqueue);
}

Uso básico en JavaScript:

Module.ccall('listInsert', null, ['number'], ['A'.charCodeAt(0)]);

---

 Gestión de Memoria

Cada estructura cuenta con un destructor manual que garantiza la eliminación de nodos creados dinámicamente, evitando pérdidas de memoria. Por ejemplo:

~LinkedList() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}


---

Compatibilidad

Sistemas operativos recomendados: Linux (nativo), Windows (vía WSL)

Requiere configuración previa de Emscripten para uso web

Estructuras compatibles con cualquier tipo de dato copiable

---

 Licencia

Proyecto desarrollado con fines exclusivamente educativos para el módulo de Estructuras de Datos Dinámicas en la carrera TNS Analista Programador (CENCO).

Autores:
Verónica Leiva – Alberto Wentelemn
© 2025

