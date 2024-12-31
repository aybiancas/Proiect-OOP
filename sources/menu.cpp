#include "../headers/menu.h"
#include "../headers/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

#include "../headers/FileLoadFailureExcept.h"

Menu* Menu::menu = nullptr;

Menu* Menu::getInstance() {
    if(menu == nullptr) {
        menu = new Menu();
    }
    return menu;
}


Menu::Menu() :
    window(nullptr),
    options({"Start", "Reguli", "Iesi"}),
    selectedOption(0),
    ruleShow(0) {
    std::cout << "Menu created" << std::endl;

    window = new sf::RenderWindow(sf::VideoMode(1300, 900), "Texas Hold' em");
    window->setFramerateLimit(20);

    if (!titleFont.loadFromFile("fonts/Bleeding_Cowboys.ttf")) {
        throw FileLoadFailure("Error: failed to load fonts");
    }

    if (!textFont.loadFromFile("fonts/BroncoPersonalUse.ttf")) {
        throw FileLoadFailure("Error: failed to load fonts");
    }

    if (!ruleFont.loadFromFile("fonts/BabelSans.ttf")) {
        throw FileLoadFailure("Error: failed to load fonts");
    }

    if(!bgImage.loadFromFile("textures/bgImage.jpg")) {
        throw FileLoadFailure("Error: failed to load background sprite");
    }

    title.setFont(titleFont);
    title.setString("Texas Hold' em");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setPosition(650 - title.getGlobalBounds().width / 2, 150);

    for (int i = 0; i < 3; ++i) {
        sf::Text optionText;
        optionText.setFont(textFont);
        optionText.setString(options[i]);
        optionText.setCharacterSize(50);
        optionText.setPosition(static_cast<float>(650 - optionText.getGlobalBounds().width / 2), static_cast<float>(350 + i * 150));
        menuOptions.push_back(optionText);
    }

    rulesText.setFont(ruleFont);
    rulesText.setCharacterSize(15);
    rulesText.setFillColor(sf::Color::White);
    rulesText.setPosition(50, 150);
}

/*
    Menu::Menu (const Menu &other) :
    window(other.window),
    options(other.options),
    selectedOption(other.selectedOption),
    ruleShow(other.ruleShow) {}
*/
    Menu::~Menu() {
        delete window;
        std::cout << "Menu closed" << std::endl;
    }
/*
    Menu& Menu::operator=(const Menu &other) {
        window = other.window;
        options = other.options;
        selectedOption = other.selectedOption;
        ruleShow = other.ruleShow;
        return *this;
    }
*/

    void Menu::drawMenu() {
        sf::Sprite sprite;
        sf::Vector2u sizeBg = bgImage.getSize();
        sf::Vector2u sizeWd = window->getSize();
        float scaleX = static_cast<float>(sizeWd.x) / static_cast<float>(sizeBg.x);
        float scaleY = static_cast<float>(sizeWd.y) / static_cast<float>(sizeBg.y);
        sprite.setTexture(bgImage);
        sprite.setScale(scaleX, scaleY);
        window->clear(sf::Color::Black);
        window->draw(sprite);
        window->draw(title);

        for (int i = 0; i < 3; ++i) {
            if (i == selectedOption) {
                menuOptions[i].setFillColor(sf::Color::Red);
            } else {
                menuOptions[i].setFillColor(sf::Color::White);
            }
            window->draw(menuOptions[i]);
        }

        window->display();
    }

    void Menu::drawRules() {
        sf::Sprite sprite;
        sf::Vector2u sizeBg = bgImage.getSize();
        sf::Vector2u sizeWd = window->getSize();
        float scaleX = static_cast<float> (sizeWd.x) / static_cast<float> (sizeBg.x);
        float scaleY = static_cast<float> (sizeWd.y) / static_cast<float> (sizeBg.y);
        sprite.setTexture(bgImage);
        sprite.setScale(scaleX, scaleY);
        window->clear(sf::Color::Black);
        window->draw(sprite);
        window->draw(rulesText);

        sf::Text backText;
        backText.setFont(textFont);
        backText.setString("< Meniu (ESC)");
        backText.setCharacterSize(40);
        backText.setPosition(40, 40);

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        if (backText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            backText.setFillColor(sf::Color::Red);
        }
        else {
            backText.setFillColor(sf::Color::White);
        }
        window->draw(backText);
        window->display();
    }

    void Menu::run () {
        std::ifstream f("rules.txt");
        std::string line, rules;
        while (std::getline(f, line)) {
            rules += line + "\n";
        }
        f.close();
        rulesText.setString(rules);
        rulesText.setCharacterSize(25);

        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                if (!ruleShow) {
                    if (event.type == sf::Event::MouseMoved) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                        selectedOption = -1;
                        for (int i = 0; i < 3; ++i) {
                            if (menuOptions[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float> (mousePos.y))) {
                                selectedOption = i;
                                break;
                            }
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        if (selectedOption == 0) {
                            std::cout << "Game started" << std::endl;
                            startGame();
                        }
                        else if (selectedOption == 1) {
                            ruleShow = true;
                            std::cout << "Rules displayed" << std::endl;
                        }
                        else if (selectedOption == 2) {
                            window->close();
                            std::cout << "Game closed" << std::endl;
                        }
                    }
                }
                else {
                    if (event.type == sf::Event::MouseButtonPressed) {
                        ruleShow = false;
                        std::cout << "Main menu displayed" << std::endl;
                    }
                }
            }
            if (ruleShow) {
                drawRules();
            }
            else {
                drawMenu();
            }
        }
    }

    void Menu::startGame() {
        Game* game = Game::getInstance();
        window->close();
        game->play();
    }

    std::ostream& operator<<(std::ostream& os, const Menu& menu) {
        for (int i = 0; i < 3; i++) {
            os << i + 1 << ". " << menu.options[i] << std::endl;
        }
        return os;
    }
