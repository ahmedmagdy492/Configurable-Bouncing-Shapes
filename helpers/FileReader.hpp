#pragma once

#include <fstream>
#include <string>
#include <vector>

class FileReader {
private:
	std::vector<std::string>* lines;
	std::string& fileName;

public:

	FileReader(std::string& fileName) : lines(new std::vector<std::string>()),
		fileName(fileName) {
	}

	~FileReader() {
		delete lines;
	}

	const std::vector<std::string>& ReadFile() const {
		std::string line;

		std::ifstream instream(fileName);

		if (instream.is_open()) {
			while (std::getline(instream, line)) {
				lines->push_back(line);
			}

			instream.close();
		}

		return *lines;
	}
};