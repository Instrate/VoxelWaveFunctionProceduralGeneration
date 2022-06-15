#pragma once

#include <fstream>
#include <filesystem>
#include <string>


std::string ReadAllText(const std::string& path) {
	std::filesystem::path dir = std::filesystem::current_path();
	std::string filepath = dir.generic_string() + path;
	std::ifstream file(filepath);
	if (file.is_open()) {
		return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	}
	return "";
}
