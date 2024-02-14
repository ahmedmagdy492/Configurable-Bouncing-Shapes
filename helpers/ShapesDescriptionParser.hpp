#pragma once

#include <iostream>
#include <vector>

#include "../helpers/Utils.hpp"
#include "../Entities/ShapeModel.hpp"

class ShapeDescriptionParser {
private:
	std::vector<ShapeModel*> *shapes;

public:
	ShapeDescriptionParser() {
		shapes = new std::vector<ShapeModel*>();
	}

	std::vector<ShapeModel*>* ParseShapeDescription(const ConfigModel& config, const std::vector<std::string>& lines) {

		for (auto& line : lines) {
			if (!line.empty()) {
				std::vector<std::string> *words = Utils::SplitString(line);
				int addedShapes = 1;

				if (words->size() > 1) {
					if ((*words)[0] == "Circle") {
						if (words->size() == 10) {
							ShapeModel* shapeModel = new ShapeModel(addedShapes++, "Circle", (*words)[1], config);

							if (Utils::ContainsDigitsOnly((*words)[2]) && Utils::ContainsDigitsOnly((*words)[3])) {
								sf::Vector2f pos(std::stoi((*words)[2]), std::stoi((*words)[3]));
								shapeModel->SeteInitialPosition(pos);

								if (Utils::ContainsDigitsOnly((*words)[4]) && Utils::ContainsDigitsOnly((*words)[5])) {
									sf::Vector2f vel(std::stoi((*words)[4]), std::stoi((*words)[5]));
									shapeModel->SetSpeed(vel);

									if (Utils::ContainsDigitsOnly((*words)[6]) && Utils::ContainsDigitsOnly((*words)[7]) && Utils::ContainsDigitsOnly((*words)[8])) {
										if (Utils::IsNumberInRange(std::stoi((*words)[6]), 0, 255) && Utils::IsNumberInRange(std::stoi((*words)[7]), 0, 255) && Utils::IsNumberInRange(std::stoi((*words)[8]), 0, 255)) {
											sf::Color color(std::stoi((*words)[6]), std::stoi((*words)[7]), std::stoi((*words)[8]));

											shapeModel->SetColor(color);

											if (Utils::ContainsDigitsOnly((*words)[9])) {
												sf::CircleShape* circle = (sf::CircleShape*)shapeModel->GetInternalShape();
												circle->setRadius(std::stoi((*words)[9]));
												shapes->push_back(shapeModel);
											}
											else {
												throw std::exception("Invalid Radius Value for Circle");
											}
										}
										else {
											throw std::exception("Invalid Color Values for Circle");
										}
									}
									else {
										throw std::exception("Invalid Color Values for Circle");
									}
								}
								else {
									throw std::exception("Invalid Speed X and Y Values for Circle");
								}
							}
							else {
								throw std::exception("Invalid X Y Values for Circle");
							}
						}
						else {
							throw std::exception("Circle Shape Expects 10 Arguments");
						}
					}
					else if ((*words)[0] == "Rectangle") {
						if (words->size() == 11) {
							ShapeModel* shapeModel = new ShapeModel(addedShapes++, "Rectangle", (*words)[1], config);

							if (Utils::ContainsDigitsOnly((*words)[2]) && Utils::ContainsDigitsOnly((*words)[3])) {
								sf::Vector2f newPos(std::stoi((*words)[2]), std::stoi((*words)[3]));
								shapeModel->SeteInitialPosition(newPos);

								if (Utils::ContainsDigitsOnly((*words)[4]) && Utils::ContainsDigitsOnly((*words)[5]))
								{
									sf::Vector2f newSpeed(std::stoi((*words)[4]), std::stoi((*words)[5]));
									shapeModel->SetSpeed(newSpeed);

									if (Utils::ContainsDigitsOnly((*words)[6]) && Utils::ContainsDigitsOnly((*words)[7]) && Utils::ContainsDigitsOnly((*words)[8])) {
										if (Utils::IsNumberInRange(std::stoi((*words)[6]), 0, 255) && Utils::IsNumberInRange(std::stoi((*words)[7]), 0, 255) && Utils::IsNumberInRange(std::stoi((*words)[8]), 0, 255)) {
											sf::Color color(std::stoi((*words)[6]), std::stoi((*words)[7]), std::stoi((*words)[8]));

											shapeModel->SetColor(color);

											if (Utils::ContainsDigitsOnly((*words)[9]) && Utils::ContainsDigitsOnly((*words)[10])) {

												sf::RectangleShape *rect = (sf::RectangleShape*)shapeModel->GetInternalShape();
												sf::Vector2f newSize(std::stoi((*words)[9]), std::stoi((*words)[10]));
												rect->setSize(newSize);

												shapes->push_back(shapeModel);
											}
											else {
												throw std::exception("Invalid Width and Height for Rectangle Color");
											}
										}
										else {
											throw std::exception("Invalid RGB Values for Rectangle Color");
										}
									}
									else {
										throw std::exception("Invalid RGB Values for Rectangle Color");
									}
								}
								else {
									throw std::exception("Invalid Speed X and Y Values for Rectangle");
								}
							}
							else {
								throw std::exception("Invalid X Y Values for Rectangle");
							}
						}
						else {
							throw std::exception("Rectangle Shape Expects 11 Arguments");
						}
					}
				}
			}
		}

		return shapes;
	}

	~ShapeDescriptionParser() {
		for (auto shape : *shapes)
			delete shape;
		delete shapes;
	}
};