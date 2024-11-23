
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"

class Menu {
    sf::RenderWindow* window;
    sf::Font titleFont;
    sf::Font textFont;
    sf::Font ruleFont;
    sf::Texture bgImage;
    sf::Text title;
    sf::Text rulesText;
    std::vector<sf::Text> menuOptions;
    std::vector<std::string> options;
    Game* game;
    int selectedOption;
    int ruleShow;

public:
    Menu();

    Menu(const Menu &other);

    ~Menu();

    Menu& operator=(const Menu &other);

    // optiuni de meniu
    // void showMenu() const;

    // alegerea optiunii de meniu
    // void selectOption(int choice);

    // void Menu::drawMenu(sf::RenderWindow &window, sf::Text &title, std::vector<sf::Text> &menuOptions, int selectedOption);
    //
    // void sfmlMainMenu();

    void drawMenu();

    void drawRules();

    void run();

    void startGame();

    // static void showRules();

    // operator cout
    friend std::ostream& operator<<(std::ostream& os, const Menu& menu);
};

#endif //MENU_H
