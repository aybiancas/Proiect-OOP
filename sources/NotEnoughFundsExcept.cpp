#include "../headers/NotEnoughFundsExcept.h"

NotEnoughFundsExcept::NotEnoughFundsExcept(std::string msg) : msg(msg) {}

const char* NotEnoughFundsExcept::what() const throw() {
    return msg.c_str();
}
