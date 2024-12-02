
#ifndef FILELOADFAILUREEXCEPT_H
#define FILELOADFAILUREEXCEPT_H

#include <exception>
#include <string>

class FileLoadFailure : public std::exception {
    std::string msg;

    public:

    explicit FileLoadFailure(const std::string msg);

    virtual const char* what() const throw();

};

#endif //FILELOADFAILUREEXCEPT_H
