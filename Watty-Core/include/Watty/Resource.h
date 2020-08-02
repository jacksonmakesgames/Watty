#pragma once
#include <vector>
#include <string>
#include <iostream>

struct Resource {
	std::string name;
	const unsigned char* data;
	const unsigned size;
	Resource(std::string name, const unsigned char* data, unsigned size) :name(name), data(data), size(size) {
	
	}

	Resource() : name(nullptr), data(nullptr), size(0){
	}
};

struct Resources {
	static std::vector<Resource*> all;
	static Resource* Load(std::string _name) {
		for (size_t i = 0; i < all.size(); i++){
			if (all[i]->name == _name) {
				return all[i];
			}
		}
		std::cout << "No resource with name: " << _name << " (Did you Init resources?)" << std::endl;
		return nullptr;
	}
};


