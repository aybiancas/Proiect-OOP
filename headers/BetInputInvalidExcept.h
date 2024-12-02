
#ifndef BETINPUTINVALIDEXCEPT_H
#define BETINPUTINVALIDEXCEPT_H

#include <exception>
#include <string>

class BetInputInvalidExcept : public std::exception {
    std::string msg;

    public:

    BetInputInvalidExcept(std::string msg);

    virtual const char* what() const throw();
};

#endif //BETINPUTINVALIDEXCEPT_H
