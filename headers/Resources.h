#ifndef RESOURCES_H
#define RESOURCES_H
#include <iostream>
#include <unordered_map>
#include <string>

#include "MapKeyIDNotFound.h"

template<typename T>
class Resources {
	std::unordered_map<std::string, T> resources;

public:
	void addResource(const std::string &id, const T &resource) {
		resources[id] = resource;
	}

	const T& getResource(const std::string &id) const {
		auto it = resources.find(id);
		if (it != resources.end()) {
			return it->second;
		}
		throw MapKeyIDNotFound("Resource with ID '" + id + "' not found.");
	}
};

#endif //RESOURCES_H
