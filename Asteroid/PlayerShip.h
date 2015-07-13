#pragma once

#include "SFML//Graphics.hpp"
#include "SFML//System.hpp"
#include "SFML//Window.hpp"
#include "SFML//Config.hpp"

#include "Object.h"

#include "Bullet.h"

template< class T >
sf::Vector3<T> Cross(sf::Vector3<T> A, sf::Vector3<T> B)
{
	return sf::Vector3<T>( A.y*B.z-A.z*B.y , A.z*B.x-A.x*B.z , A.x*B.y-A.y*B.x );
}

template< class T >
T Norm(sf::Vector3<T> A)
{
	return sqrt(A.x*A.x+A.y*A.y+A.z*A.z);
}

template< class T >
T Norm(sf::Vector2<T> A)
{
	return sqrt(A.x*A.x+A.y*A.y);
}

#include <vector>

class Game;

class PlayerShip: public Object
{
private:
	Game* m_pGame;

	sf::Font* m_pLabelFont;

	sf::String m_Label;

	sf::Image* m_ShotImage;

	std::vector<sf::Sprite> m_ShotSpritesArray;

	sf::Vector2<float> m_Force;

	sf::Vector2<float> m_Direction;

	sf::Vector2<float> m_Velocity;

	sf::Vector2<float> m_Acceleration;
	float m_ConstForce;

	float m_AngularVelocity;

	bool m_TurnLeftFlag;
	bool m_TurnRightFlag;
	bool m_MoveForwardFlag;
	bool m_MoveBackwardFlag;

	bool m_DamageOnTick;

	const float m_Mass;

	const float m_Friction;

	const float m_InertiaMoment;

	const float m_MaxVelocity;

	void _DrawArrow(sf::RenderWindow& RW, sf::Vector2<float>& Vec, sf::Color color, float scale = 1.0f);

public:
	PlayerShip(sf::Image* image, sf::Image* shot, Game* game, float initX, float initY);

	~PlayerShip();

	void MoveForward ();

	void MoveBackward();

	void TurnLeft    ();

	void TurnRight   ();

	void Shot();

	void Update(float elapsedTime);

	void Draw(sf::RenderWindow& RW);

	void ResolveCollision(sf::Vector2<float> normal);

};