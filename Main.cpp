#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"

#include "helpers/FileReader.hpp"
#include "helpers/ConfigParser.hpp"
#include "helpers/ShapesDescriptionParser.hpp"
#include "Entities/ShapeModel.hpp"

#include <iostream>

int main() {

	std::string filePath = "config file.txt";
	FileReader fr(filePath);
	std::vector<std::string> lines = fr.ReadFile();

	if (lines.size() == 0) {
		std::cout << "Cannot read the specified config file " << filePath << std::endl;
		return EXIT_FAILURE;
	}

	ConfigModel config;

	try {
		ConfigParser cp;
		config = cp.ParseConfig(lines);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	sf::RenderWindow window(sf::VideoMode(config.width, config.height), "SFML Proj 1");

	sf::Font font = sf::Font();
	if (!font.loadFromFile(config.fontPath)) {
		std::cout << "Unable to Load Font: " << config.fontPath << std::endl;
	}

	ShapeDescriptionParser shapeDescParser;
	std::vector<ShapeModel*>* shapesToDraw = NULL;
	
	try {
		shapesToDraw = shapeDescParser.ParseShapeDescription(lines);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	size_t shapeCounter = 0, shapesCount = shapesToDraw->size();

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(0, 0, 0));

		for (shapeCounter = 0; shapeCounter < shapesCount; ++shapeCounter) {
			ShapeModel* curShape = (*shapesToDraw)[shapeCounter];

			if (curShape->ShouldDrawShape()) {
				window.draw(*curShape->GetInternalShape());

				curShape->Move(config.width, config.height);
			}
		}

		window.display();
	}

	return EXIT_SUCCESS;
}