#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"

#include "helpers/FileReader.hpp"
#include "helpers/ConfigParser.hpp"
#include "helpers/ShapesDescriptionParser.hpp"
#include "Entities/ShapeModel.hpp"

#include <iostream>

int main() {

	std::string filePath = "config.txt";
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

	ImGui::SFML::Init(window);

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
	ShapeModel* curSelectedShape = NULL;
	char shapeName[1024];

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		ImGui::SFML::Update(window, sf::seconds(1.0f/60.0f));

		ImGui::Begin("Shape Properties");

		if (ImGui::BeginCombo("Shapes", curSelectedShape == NULL ? "Select Shape" : curSelectedShape->GetName().c_str())) {
			for (shapeCounter = 0; shapeCounter < shapesCount; ++shapeCounter) {
				ShapeModel* curShape = (*shapesToDraw)[shapeCounter];
				bool isSelected;
				
				if (ImGui::Selectable(curShape->GetName().c_str(), &isSelected)) {
					curSelectedShape = curShape;
				}
			}
			ImGui::EndCombo();
		}
		
		if (curSelectedShape != NULL) {
			bool shouldDrawShape = curSelectedShape->ShouldDrawShape();
			if (ImGui::Checkbox("Draw Shape", &shouldDrawShape)) {
				curSelectedShape->SetDrawShape(shouldDrawShape);
			}

			float scale = curSelectedShape->GetInternalShape()->getScale().x;
			if (ImGui::SliderFloat("Scale", &scale, 1, 3)) {
				curSelectedShape->SetScale(scale);
			}

			float vel[2] = { curSelectedShape->GetSpeed().x, curSelectedShape->GetSpeed().y };
			if (ImGui::SliderFloat2("Velocity", vel, -5, 5)) {
				curSelectedShape->SetSpeed(sf::Vector2f(vel[0], vel[1]));
			}

			sf::Color color = curSelectedShape->GetInternalShape()->getFillColor();
			float colors[3] = { color.r/255.0f, color.g/255.0f, color.b/255.0f };

			if (ImGui::ColorEdit3("Color", colors)) {
				curSelectedShape->SetColor(sf::Color(colors[0]*255.0f, colors[1] * 255.0f, colors[2] * 255.0f));
			}

			memset(shapeName, 0, sizeof(shapeName) / sizeof(char));
			memcpy(shapeName, curSelectedShape->GetName().c_str(), sizeof(shapeName)/sizeof(char));
			if (ImGui::InputText("Name", shapeName, sizeof(shapeName) / sizeof(char)), ImGuiInputTextFlags_EnterReturnsTrue) {
				curSelectedShape->SetName(shapeName);
			}
		}

		ImGui::End();

		window.clear(sf::Color(0, 0, 0));

		for (shapeCounter = 0; shapeCounter < shapesCount; ++shapeCounter) {
			ShapeModel* curShape = (*shapesToDraw)[shapeCounter];

			if (curShape->ShouldDrawShape()) {
				window.draw(*curShape->GetInternalShape());

				curShape->Move(config.width, config.height);
			}
		}

		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown();

	return EXIT_SUCCESS;
}