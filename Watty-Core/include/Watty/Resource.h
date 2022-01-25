#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct Resource {
	std::string name;
	const unsigned char* data;
	unsigned size;
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

	static Resource* UpdateResourceWithData(std::string _name, const unsigned char* data, unsigned size) {
		for (size_t i = 0; i < all.size(); i++) {
			if (all[i]->name == _name) {
				all[i]->data = data;
				all[i]->size = size;
				return all[i];
			}
		}
		std::cout << "No resource with name: " << _name << " (Did you Init resources?)" << std::endl;
		return nullptr;
	}

	static Resource* UpdateResourceFromDisk(std::string _name, const std::string& filepath){
		// load file data
		std::pair<const unsigned char*, size_t> dataAndSize = LoadDataFromDisk(filepath);
		// update resource
		return UpdateResourceWithData(_name, dataAndSize.first, dataAndSize.second);
	}

	static std::pair<const unsigned char*, size_t> LoadDataFromDisk(const std::string& filepath){
		std::ifstream file(filepath, std::ios::binary);
		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}
		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		const unsigned char* data = reinterpret_cast<const unsigned char*>(buffer.data());

		return std::pair(data, fileSize);
	}

	static Resource* AddExternalFileAtRunTime(const std::string& filepath, std::string _name) {
		for (size_t i = 0; i < all.size(); i++){
			if (all[i]->name == _name) {
				std::cout<<"Resource with name: "<<_name<<" already exists!"<<std::endl;
				return all[i];
			}
		}

		// load file data
		std::pair<const unsigned char*, size_t> dataAndSize = LoadDataFromDisk(filepath);

		if( dataAndSize.second > UINT_MAX ) {
			std::cout << "ERROR READING FILE: " << filepath << " TOO BIG!" << std::endl;
			return nullptr;
    	}
		else{
			unsigned l = static_cast<unsigned>(dataAndSize.second);
			auto res = new Resource(_name, dataAndSize.first, l);
			all.push_back(res);
			return res;
		}
		
	}
};


