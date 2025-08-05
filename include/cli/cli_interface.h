#pragma once
#include <functional>
#include <vector>
#include <string>


namespace CLI {
    // Opción de menú
    struct MenuOption {
        std::string description;
        std::function<void()> action;
    };

    // Menú interactivo
    class InteractiveMenu {
        std::vector<MenuOption> options;
        std::string title;
        
    public:
        InteractiveMenu(const std::string& title) : title(title) {}
        void addOption(const std::string& desc, std::function<void()> action);
        void display() const;
        void run();
    };

    // Funciones de demostración
    void runLinkedListDemo();
    void runStackDemo();
    void runQueueDemo();
    void runMainMenu();
}