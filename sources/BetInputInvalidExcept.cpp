#include "../headers/BetInputInvalidExcept.h"

BetInputInvalidExcept::BetInputInvalidExcept(const std::string msg) : msg(msg) {}

const char* BetInputInvalidExcept::what() const throw() {
    return msg.c_str();
}
