#include <iostream>
#include <random>
#include <fstream>
#include "headers/menu.h"

int main() {

    // menu test

    std::ifstream f("tastatura.txt");
    int choice;
    f >> choice;
    f.close();

    Menu menu;
    menu.run(choice);

}
