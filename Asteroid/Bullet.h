#pragma once

#include "SFML//Graphics.hpp"
#include "SFML//System.hpp"
#include "SFML//Window.hpp"
#include "SFML//Config.hpp"

#include "Object.h"


class Bullet: public Object
{
private:

	sf::Vector2<float> m_Velocity;

public:
	Bullet(sf::Image* image, sf::Vector2<float> position, sf::Vector2<float> direction, float speed);

	~Bullet();

	void Update(float elapsedTime);

	void Draw(sf::RenderWindow& RW);

};