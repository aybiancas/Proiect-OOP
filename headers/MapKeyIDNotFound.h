
#ifndef MAPKEYIDNOTFOUND_H
#define MAPKEYIDNOTFOUND_H

#include <exception>
#include <string>

class MapKeyIDNotFound : public std::exception {
	std::string msg;

public:

	explicit MapKeyIDNotFound(const std::string& msg);

	virtual const char* what() const throw();
};

#endif //MAPKEYIDNOTFOUND_H
