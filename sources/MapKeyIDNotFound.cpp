#include "../headers/MapKeyIDNotFound.h"

MapKeyIDNotFound::MapKeyIDNotFound(const std::string &msg) : msg(msg) {}

const char* MapKeyIDNotFound::what() const throw() {
	return msg.c_str();
}
