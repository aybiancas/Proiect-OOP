#include "../headers/FileLoadFailureExcept.h"

FileLoadFailure::FileLoadFailure(std::string msg) : msg(msg) {}

const char* FileLoadFailure::what() const throw() {
    return msg.c_str();
}
