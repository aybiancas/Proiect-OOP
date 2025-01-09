#ifndef RESOURCES_H
#define RESOURCES_H
#include <iostream>
#include <unordered_map>
#include <string>

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
		throw std::runtime_error("Resource with ID '" + id + "' not found.");
		// std::cout << "Resource with id " << id << " not found" << std::endl;
	}
};

#endif //RESOURCES_H
