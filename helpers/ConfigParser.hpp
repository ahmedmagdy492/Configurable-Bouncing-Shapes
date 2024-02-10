#pragma once

#include <iostream>
#include <string>
#include <vector>



#include "../Entities/ConfigModel.hpp"
#include "../helpers/Utils.hpp"


class ConfigParser {

public:
	ConfigModel ParseConfig(const std::vector<std::string>& lines) {
		size_t size = lines.size();
		ConfigModel config;

		for (auto& line : lines) {
			if (!line.empty()) {
				std::vector<std::string>* words = Utils::SplitString(line);

				if (words->size() > 1) {
					if ((*words)[0] == "Window") {
						if (words->size() < 3) {
							throw std::exception("Window Directive Expects 2 Arguments");
						}

						if (Utils::ContainsDigitsOnly((*words)[1])) {
							config.width = std::stoi((*words)[1]);

							if (Utils::ContainsDigitsOnly((*words)[2])) {
								config.height = std::stoi((*words)[2]);
							}
							else {
								throw std::exception("Window Height has to be a valid number");
							}
						}
						else {
							throw std::exception("Window Width has to be a valid number");
						}
					}
					else if ((*words)[0] == "Font") {
						if (words->size() == 6) {
							config.fontPath = (*words)[1];

							if (Utils::ContainsDigitsOnly((*words)[2])) {
								config.fontSize = std::stoi((*words)[2]);

								if (Utils::ContainsDigitsOnly((*words)[3]) && Utils::ContainsDigitsOnly((*words)[4]) && Utils::ContainsDigitsOnly((*words)[5])) {
									config.fontColor = sf::Color(std::stoi((*words)[3]), std::stoi((*words)[4]), std::stoi((*words)[5]));
								}
								else {
									throw std::exception("Font Color Should be a Valid Number");
								}
							}
							else {
								throw std::exception("Font Size Should be a Valid Number");
							}
						}
						else {
							throw std::exception("Font Directive Expects 6 Arguments");
						}
					}
				}
			}
		}

		return config;
	}
};