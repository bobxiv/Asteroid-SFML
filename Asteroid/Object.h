#pragma once

#include "SFML//Graphics.hpp"
#include "SFML//System.hpp"
#include "SFML//Window.hpp"
#include "SFML//Config.hpp"


class Object
{
protected:

	sf::Sprite m_Sprite;

	sf::Image* m_Image;

	sf::Rect<float> m_Bound;

public:
	//Bullet(sf::Image* image, sf::Vector2<float> position, sf::Vector2<float> direction);

	//~Bullet();

	virtual void Update(float elapsedTime) = 0;

	virtual void Draw(sf::RenderWindow& RW) = 0;

	sf::Vector2<float> GetPosition();

	static bool Collide(Object& A, Object& B);

};