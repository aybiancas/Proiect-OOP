#include "headers/menu.h"
#include "headers/BetInputInvalidExcept.h"
#include "headers/FileLoadFailureExcept.h"
#include "headers/NotEnoughFundsExcept.h"

int main() {

    try {
        Menu menu;
        menu.run();
    } catch (FileLoadFailure& e) {
        std::cout << "FileLoadFailure: " << e.what() << std::endl;
    } catch (NotEnoughFundsExcept& e) {
        std::cout << "NotEnoughFundsExcept: " << e.what() << std::endl;
    } catch (BetInputInvalidExcept& e) {
        std::cout << "BetInputInvalidExcept: " << e.what() << std::endl;
    }

}
