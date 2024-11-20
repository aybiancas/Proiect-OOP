#include "../headers/menu.h"
#include "../headers/game.h"
#include <iostream>
#include <fstream>

    Menu::Menu() :
    options({"Start", "Reguli", "Iesi"}),
    game(nullptr) {
        std::cout << "Meniu creat." << std::endl;
    }

    Menu::Menu (const Menu &other) : options(other.options), game(other.game) {}

    Menu::~Menu() {
        delete game;
        std::cout << "Meniu inchis." << std::endl;
    }

    Menu& Menu::operator=(const Menu &other) {
        options = other.options;
        game = other.game;
        return *this;
    }

    // optiuni de meniu
    void Menu::showMenu() const {
        std::cout << "Texas Hold' em" << std::endl;
        for(int i = 0; i < 3; i++) {
            std::cout << i + 1 << ". " << options[i] << std::endl;
        }
    }

    // alegerea optiunii de meniu
    void Menu::selectOption(int choice) {
        std::cout << "Optiune: ";

        switch (choice) {
            case 1:
                std::cout << "Incepe jocul ..." << std::endl;
            startGame();
            // apelare functie de joc
            break;

            case 2:
                std::cout << "Reguli: [...]" << std::endl;
            showRules();
            // idee: sa ramana in meniu inainte de a inchide meniul
            break;

            case 3:
                std::cout << "Se inchide ..." << std::endl;
            // opreste programul
            break;

            default:
                std::cout << "Invalid ..." << std::endl;
            // in cazul inputului de la user in consola, urmatoarele doua linii de cod comentat merg
            // showMenu();
            // selectOption(choice);
            // afiseaza din nou optiunile din meniu
        }
    }

    void Menu::run (int choice) {
        showMenu();
        selectOption(choice);
    }

    void Menu::startGame() {
        if (game != nullptr) {
            delete game;
        }
        game = new Game();
        game->play();
    }

    void Menu::showRules () {
        // citeste fisierul de reguli si le afiseaza pe ecran
        std::ifstream f("../rules.txt");
        std::string line;
        while (std::getline(f, line)) {
            std::cout << line << std::endl;
        }
        f.close();
        std::cout << std::endl;
    }

    // operator cout
    std::ostream& operator<<(std::ostream& os, const Menu& menu) {
        for (int i = 0; i < 3; i++) {
            os << i + 1 << ". " << menu.options[i] << std::endl;
        }
        return os;
    }