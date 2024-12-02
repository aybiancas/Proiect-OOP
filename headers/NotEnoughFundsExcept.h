
#ifndef NOTENOUGHFUNDSEXCEPT_H
#define NOTENOUGHFUNDSEXCEPT_H

#include <exception>
#include <string>

class NotEnoughFundsExcept : public std::exception {
    std::string msg;

    public:

    NotEnoughFundsExcept(std::string msg);

    virtual const char* what() const throw();
};

#endif //NOTENOUGHFUNDSEXCEPT_H