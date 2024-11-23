#include "../headers/menu.h"
#include "../headers/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

    Menu::Menu() :
    window(nullptr),
    options({"Start", "Reguli", "Iesi"}),
    game(nullptr),
    selectedOption(0),
    ruleShow(0) {

        std::cout << "Meniu creat." << std::endl;

        window = new sf::RenderWindow(sf::VideoMode(1300, 900), "Texas Hold' em");
        window->setFramerateLimit(20);

        if (!titleFont.loadFromFile("fonts/Bleeding_Cowboys.ttf")) {
            std::cout << "Error. Could not load font." << std::endl;
        }

        if (!textFont.loadFromFile("fonts/BroncoPersonalUse.ttf")) {
            std::cout << "Error. Could not load font." << std::endl;
        }

        if (!ruleFont.loadFromFile("fonts/BabelSans.ttf")) {
            std::cout << "Error. Could not load font." << std::endl;
        }

        if(!bgImage.loadFromFile("textures/bgImage.jpg")) {
            std::cout << "Error. Could not load image." << std::endl;
        }

        title.setFont(titleFont);
        title.setString("Texas Hold' em");
        title.setCharacterSize(100);
        title.setFillColor(sf::Color::White);
        title.setPosition(650 - title.getGlobalBounds().width / 2, 150);

        for (int i = 0; i < options.size(); ++i) {
            sf::Text optionText;
            optionText.setFont(textFont);
            optionText.setString(options[i]);
            optionText.setCharacterSize(50);
            optionText.setPosition(static_cast<float> (650 - optionText.getGlobalBounds().width / 2), static_cast<float> (350 + i * 150));
            menuOptions.push_back(optionText);
        }

        rulesText.setFont(ruleFont);
        rulesText.setCharacterSize(15);
        rulesText.setFillColor(sf::Color::White);
        rulesText.setPosition(50, 150);
    }

    Menu::Menu (const Menu &other) : window(other.window), options(other.options),
    game(other.game), selectedOption(other.selectedOption), ruleShow(other.ruleShow) {}

    Menu::~Menu() {
        delete game;
        delete window;
        std::cout << "Meniu inchis." << std::endl;
    }

    Menu& Menu::operator=(const Menu &other) {
        window = other.window;
        options = other.options;
        game = other.game;
        selectedOption = other.selectedOption;
        ruleShow = other.ruleShow;
        return *this;
    }


    // optiuni de meniu
    void Menu::showMenu() const {
        std::cout << "Texas Hold' em" << std::endl;
        for(int i = 0; i < 3; i++) {
            std::cout << i + 1 << ". " << options[i] << std::endl;
        }
    }

    // // alegerea optiunii de meniu
    // void Menu::selectOption(int choice) {
    //     std::cout << "Optiune: ";
    //
    //     switch (choice) {
    //         case 1:
    //             std::cout << "Incepe jocul ..." << std::endl;
    //         startGame();
    //         // apelare functie de joc
    //         break;
    //
    //         case 2:
    //             std::cout << "Reguli: [...]" << std::endl;
    //         showRules();
    //         // idee: sa ramana in meniu inainte de a inchide meniul
    //         break;
    //
    //         case 3:
    //             std::cout << "Se inchide ..." << std::endl;
    //         // opreste programul
    //         break;
    //
    //         default:
    //             std::cout << "Invalid ..." << std::endl;
    //     }
    // }


    void Menu::drawMenu() {
        sf::Sprite sprite;
        sf::Vector2u sizeBg = bgImage.getSize();
        sf::Vector2u sizeWd = window->getSize();
        float scaleX = static_cast<float> (sizeWd.x) / static_cast<float> (sizeBg.x);
        float scaleY = static_cast<float> (sizeWd.y) / static_cast<float> (sizeBg.y);
        sprite.setTexture(bgImage);
        sprite.setScale(scaleX, scaleY);
        window->clear(sf::Color::Black);
        window->draw(sprite);
        window->draw(title);

        for (size_t i = 0; i < menuOptions.size(); ++i) {
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
                        for (int i = 0; i < menuOptions.size(); ++i) {
                            if (menuOptions[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float> (mousePos.y))) {
                                selectedOption = i;
                                break;
                            }
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        if (selectedOption == 0) {
                            startGame();
                            std::cout << "Joc inceput" << std::endl;
                        }
                        else if (selectedOption == 1) {
                            ruleShow = true;
                            std::cout << "Reguli afisate pe ecran" << std::endl;
                        }
                        else if (selectedOption == 2) {
                            window->close();
                            std::cout << "Joc inchis" << std::endl;
                        }
                    }
                }
                else {
                    if (event.type == sf::Event::MouseButtonPressed) {
                        ruleShow = false;
                        std::cout << "Meniu afisat" << std::endl;
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
        if (game != nullptr) {
            delete game;
        }
        game = new Game();
        window->close();
        game->play();
    }

    // operator cout
    std::ostream& operator<<(std::ostream& os, const Menu& menu) {
        for (int i = 0; i < 3; i++) {
            os << i + 1 << ". " << menu.options[i] << std::endl;
        }
        return os;
    }