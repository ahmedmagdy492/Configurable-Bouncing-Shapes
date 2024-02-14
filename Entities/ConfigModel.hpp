#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

struct ConfigModel {
	std::string fontPath;
	size_t fontSize;
	sf::Color fontColor;
	sf::Font* font;
	int width;
	int height;
};