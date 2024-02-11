#pragma once

#include <iostream>
#include <sstream>

#include "SFML/Graphics.hpp"

#include "../helpers/ShapeFactory.hpp"

class ShapeModel {
private:
	long id;
	sf::Shape* shape;
	sf::Vector2f speed;
	bool drawShape;
	std::string name;

public:
	ShapeModel(long id, const std::string& shapeName, const std::string& friendlyName) : id(id), drawShape(true), name(friendlyName) {
		shape = ShapeFactory::CreateShape(shapeName);
		if (shape == NULL) {
			std::stringstream msg;
			msg << "Shape " << shapeName << " is not supported";
			throw std::exception(msg.str().c_str());
		}
	}

	~ShapeModel() {
		delete shape;
	}

	long GetId() const {
		return id;
	}

	const sf::Shape* GetInternalShape() const {
		return shape;
	}

	const sf::Vector2f& GetPosition() const {
		return shape->getPosition();
	}

	void SetSpeed(const sf::Vector2f& newSpeed) {
		speed = newSpeed;
	}

	const sf::Vector2f& GetSpeed() {
		return speed;
	}

	bool ShouldDrawShape() const {
		return drawShape;
	}

	void SetDrawShape(bool drawShape) {
		this->drawShape = drawShape;
	}

	void SetColor(sf::Color newColor) {
		this->shape->setFillColor(newColor);
	}

	void SetScale(double newScaleValue) {
		if (newScaleValue > 0 && newScaleValue < 5) {
			this->shape->setScale(newScaleValue, newScaleValue);
		}
	}

	const std::string& GetName() const {
		return name;
	}

	void SetName(const std::string& newName) {
		this->name = newName;
	}

	void SeteInitialPosition(sf::Vector2f position) {
		this->shape->setPosition(position);
	}

	void Move(int width, int height) {
		sf::Vector2f curPos = this->shape->getPosition();

		if (Utils::instanceof<sf::CircleShape>(this->shape)) {
			sf::CircleShape* circle = (sf::CircleShape*)this->shape;
			if ((curPos.x + speed.x) <= 0 || (curPos.x + speed.x + circle->getRadius()*2*circle->getScale().x) >= width) {
				SetSpeed(sf::Vector2f(speed.x * -1, speed.y));
			}
			else if ((curPos.y + speed.y) <= 0 || (curPos.y + speed.y + circle->getRadius()*2*circle->getScale().y) >= height) {
				SetSpeed(sf::Vector2f(speed.x, speed.y*-1));
			}
			circle->setPosition(curPos + speed*0.15f);
		}
		else {
			sf::RectangleShape* rect = (sf::RectangleShape*)this->shape;
			if ((curPos.x + speed.x) <= 0 || (curPos.x + speed.x + rect->getSize().x*rect->getScale().x) >= width) {
				SetSpeed(sf::Vector2f(speed.x * -1, speed.y));
			}
			else if ((curPos.y + speed.y) <= 0 || (curPos.y + speed.y + rect->getSize().y*rect->getScale().y) >= height) {
				SetSpeed(sf::Vector2f(speed.x, speed.y * -1));
			}
			rect->setPosition(curPos + speed * 0.15f);
		}
	}
};