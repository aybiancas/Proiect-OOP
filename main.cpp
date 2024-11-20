#include <iostream>
#include <random>
#include <fstream>
#include "headers/menu.h""


// De adaugat logica joc:
// evaluatorul de carti si definirea unui handValue pentru a decide ce grupare este mai buna
// + tiebreaker
// implementarea de ture
// ideea de call, raise, fold pentru player 1
// + functie de all in pt raise
// + caz pt call in care unul din playeri nu are suma necesara pt call -- automat fold
// automat implementare de suma pentru betting (~500/1000?) si oprirea jocului cand un player are suma = 0



int main() {

    //test meniu

    std::ifstream f("tastatura.txt");
    int choice;
    f >> choice;
    f.close();

    Menu menu;
    menu.run(choice);



    // test joc
    // Game game;
    // game.play();
    // return 0;
}
