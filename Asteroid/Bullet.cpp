#include "PlayerShip.h"

/////////////////////////////////////////////////////////////////////////////
////////////////				Constructors				/////////////////
/////////////////////////////////////////////////////////////////////////////

Bullet::Bullet(sf::Image* image, sf::Vector2<float> position, sf::Vector2<float> direction, float speed)
{
	m_Image = image;

	m_Sprite.SetImage(*image);
	sf::Vector2<float> aux = m_Sprite.GetSize();
	m_Sprite.SetCenter(aux.x/2.0f, aux.y/2.0f);

	m_Velocity = direction*speed;

	m_Sprite.SetPosition(position);
}

/////////////////////////////////////////////////////////////////////////////
////////////////				Methods						/////////////////
/////////////////////////////////////////////////////////////////////////////

void Bullet::Update(float elapsedTime)
{
	sf::Vector2<float> size   = m_Sprite.GetSize();
	sf::Vector2<float> center = m_Sprite.GetPosition();
	m_Bound.Left   = center.x-size.x/2.0f/2.8f;
	m_Bound.Right  = center.x+size.x/2.0f/2.8f;
	m_Bound.Top    = center.y-size.y/2.0f/2.8f;
	m_Bound.Bottom = center.y+size.y/2.0f/2.8f;

	m_Sprite.Move(m_Velocity*elapsedTime);
}

void Bullet::Draw(sf::RenderWindow& RW)
{
	RW.Draw(m_Sprite);
	sf::Shape collisionBound = sf::Shape::Rectangle(m_Bound.Left, m_Bound.Top, m_Bound.Right, m_Bound.Bottom, sf::Color(255,255,255,0), 1, sf::Color::Yellow);
	RW.Draw(collisionBound);
}