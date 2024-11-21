#include <iostream>
#include <random>
#include <fstream>
#include "headers/menu.h"


//test reupstream

int main() {

    // menu test

    std::ifstream f("tastatura.txt");
    int choice;
    f >> choice;
    f.close();

    Menu menu;
    menu.run(choice);

}
