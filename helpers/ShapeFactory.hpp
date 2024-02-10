#pragma once

#include "SFML/Graphics.hpp"

class ShapeFactory {
public:
	static sf::Shape* CreateShape(const std::string& shapeName) {
		if (shapeName == "Rectangle") {
			return new sf::RectangleShape();
		}
		else if (shapeName == "Circle") {
			return new sf::CircleShape();
		}

		return NULL;
	}
};