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
	sf::Text text;

public:
	ShapeModel(long id, const std::string& shapeName, const std::string& friendlyName, const ConfigModel& config) : id(id), drawShape(true), name(friendlyName) {
		shape = ShapeFactory::CreateShape(shapeName);
		if (shape == NULL) {
			std::stringstream msg;
			msg << "Shape " << shapeName << " is not supported";
			throw std::exception(msg.str().c_str());
		}
		text.setString(friendlyName);
		text.setFillColor(config.fontColor);
		text.setFont(*config.font);
		text.setCharacterSize(config.fontSize);
		text.setStyle(sf::Text::Bold);
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

			sf::FloatRect boundBox = circle->getGlobalBounds();

			if (boundBox.left <= 0.0f || (boundBox.left + boundBox.width) >= width) {
				SetSpeed(sf::Vector2f(speed.x*-1, speed.y));
			}
			else if (boundBox.top <= 0.0f || (boundBox.top + boundBox.height) >= height) {
				SetSpeed(sf::Vector2f(speed.x, speed.y * -1));
			}
			circle->move(speed);
		}
		else {
			sf::RectangleShape* rect = (sf::RectangleShape*)this->shape;
			sf::FloatRect boundBox = rect->getGlobalBounds();

			if (boundBox.left <= 0 || (boundBox.left + boundBox.width) >= width) {
				SetSpeed(sf::Vector2f(speed.x * -1, speed.y));
			}
			else if (boundBox.top <= 0 || (boundBox.top + boundBox.height) >= height) {
				SetSpeed(sf::Vector2f(speed.x, speed.y * -1));
			}
			rect->move(speed);

			//text.setPosition((rect->getPosition().x+rect->getSize().x- text.getGlobalBounds().width)/2, (rect->getPosition().y + rect->getSize().y- text.getGlobalBounds().height)/2);
		}
	}

	const sf::Text GetText() const {
		return text;
	}
};