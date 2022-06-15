#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "FileLoader.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

class EngineSettings {
public:
	
	ptree source;

	explicit EngineSettings(const std::string& configFile = "/config.json") {
		LoadFromFile(configFile);
	}

	bool LoadFromFile(const std::string& configFile) {
		std::string file_content = ReadAllText(configFile);
		std::istringstream is(file_content);
		read_json(is, source);
		return true;
	}
	
	std::string PathShaderGetValue(const std::string& key) {
		return source.get<std::string>("PATH.SHADER." + key);
	}

	std::vector<int> PathWindowSizeGetValue() {
		return std::vector<int> {
			source.get<int>("WINDOW.SIZE.WIDTH"),
			source.get<int>("WINDOW.SIZE.HEIGHT")
		};
	}

	std::string PathWindowNameGetValue() {
		return source.get<std::string>("WINDOW.NAME");
	}

};