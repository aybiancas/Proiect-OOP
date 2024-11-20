
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "game.h"

class Menu {
    std::vector<std::string> options;
    Game* game;

public:
    Menu();

    Menu(const Menu &other);

    ~Menu();

    Menu& operator=(const Menu &other);

    // optiuni de meniu
    void showMenu() const;

    // alegerea optiunii de meniu
    void selectOption(int choice);

    void run(int choice);

    void startGame();

    static void showRules();

    // operator cout
    friend std::ostream& operator<<(std::ostream& os, const Menu& menu);
};

#endif //MENU_H
