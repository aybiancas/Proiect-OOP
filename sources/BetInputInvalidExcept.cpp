#include "../headers/BetInputInvalidExcept.h"

BetInputInvalidExcept::BetInputInvalidExcept(std::string msg) : msg(msg) {}

const char* BetInputInvalidExcept::what() const throw() {
    return msg.c_str();
}
