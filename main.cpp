#include "headers/Menu.h"
#include "headers/BetInputInvalidExcept.h"
#include "headers/FileLoadFailureExcept.h"
#include "headers/NotEnoughFundsExcept.h"

int main() {

    Menu* menu = Menu::getInstance();
    try {
        menu->run();
    } catch (FileLoadFailure& e) {
        std::cout << "FileLoadFailure: " << e.what() << std::endl;
    } catch (NotEnoughFundsExcept& e) {
        std::cout << "NotEnoughFundsExcept: " << e.what() << std::endl;
    } catch (BetInputInvalidExcept& e) {
        std::cout << "BetInputInvalidExcept: " << e.what() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << "runtime_error: " << e.what() << std::endl;
    }

}
