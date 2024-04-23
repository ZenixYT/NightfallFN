#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

namespace Utils
{
	std::vector<std::string> splitString(std::string s, char delimiter)
	{
        std::vector<std::string> tokens;
        size_t start = 0, end = 0;
        while ((end = s.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(s.substr(start));
        return tokens;
	}

    std::string readFile(const std::string& file_path) {
        std::ifstream file(file_path);
        std::string file_contents;

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                file_contents += line;
                file_contents.push_back('\n');
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open file: " << file_path << std::endl;
        }

        return file_contents;
    }
}