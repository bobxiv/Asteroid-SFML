#include "PlayerShip.h"

#include "Game.h"

/////////////////////////////////////////////////////////////////////////////
////////////////				Constructors				/////////////////
/////////////////////////////////////////////////////////////////////////////

PlayerShip::PlayerShip(sf::Image* image, sf::Image* shot, Game* game, float initX, float initY): m_ShotImage(shot),
		m_MaxVelocity(10), m_Mass(1), m_InertiaMoment(1), m_Friction(0.1f), m_TurnLeftFlag(false), m_TurnRightFlag(false), m_MoveForwardFlag(false), m_MoveBackwardFlag(false), m_pGame(game), m_DamageOnTick(false)
{
	m_Image = image;

	m_Sprite.SetImage(*image);
	sf::Vector2<float> aux = m_Sprite.GetSize();
	m_Sprite.SetCenter(aux.x/2.0f, aux.y/2.0f);

	m_pLabelFont = new sf::Font();
	if( !m_pLabelFont->LoadFromFile("arial.ttf") )
		throw( new std::exception("PlayerShip::PlayerShip -> No se encuentra la fuente: arial.ttf") );
	m_Label.SetFont(*m_pLabelFont);

	m_Direction.x = 0;
	m_Direction.y = -1;

	m_Force.x = 0;
	m_Force.y = 0;

	m_Velocity.x = 0;
	m_Velocity.y = 0;

	m_Acceleration.x = 0;
	m_Acceleration.y = 0;

	//m_ConstForce = 0.65f;
	m_ConstForce = 300.0f;

	m_AngularVelocity = 1;

	m_Sprite.SetPosition(initX,initY);

	sf::Vector2<float> size   = m_Sprite.GetSize();
	sf::Vector2<float> center = m_Sprite.GetPosition();
	m_Bound.Left   = center.x-size.x/2.0f;
	m_Bound.Right  = center.x+size.x/2.0f;
	m_Bound.Top    = center.y-size.y/2.0f;
	m_Bound.Bottom = center.y+size.y/2.0f;
	
}

PlayerShip::~PlayerShip()
{
	delete m_pLabelFont;
}

/////////////////////////////////////////////////////////////////////////////
////////////////				Methods						/////////////////
/////////////////////////////////////////////////////////////////////////////

void PlayerShip::Update(float elapsedTime)
{
	sf::Vector2<float> size   = m_Sprite.GetSize();
	sf::Vector2<float> center = m_Sprite.GetPosition();
	m_Bound.Left   = center.x-size.x/2.0f;
	m_Bound.Right  = center.x+size.x/2.0f;
	m_Bound.Top    = center.y-size.y/2.0f;
	m_Bound.Bottom = center.y+size.y/2.0f;

	if( m_TurnLeftFlag )
	{
		float angularDispl = m_AngularVelocity * elapsedTime;
		m_Direction.x =  cos(angularDispl)*m_Direction.x + sin(angularDispl)*m_Direction.y;
		m_Direction.y = -sin(angularDispl)*m_Direction.x + cos(angularDispl)*m_Direction.y;
		this->m_Sprite.Rotate(angularDispl*180/3.1415f);
		m_TurnLeftFlag  = false;
		m_TurnRightFlag = false;
	}else if( m_TurnRightFlag )
		{
			float angularDispl = m_AngularVelocity * elapsedTime;
			m_Direction.x = cos(angularDispl)*m_Direction.x - sin(angularDispl)*m_Direction.y;
			m_Direction.y = sin(angularDispl)*m_Direction.x + cos(angularDispl)*m_Direction.y;
			this->m_Sprite.Rotate(-angularDispl*180/3.1415f);
			m_TurnRightFlag = false;
		}

	if( m_MoveForwardFlag )
	{
		m_Force           += m_ConstForce*m_Direction;
		m_MoveForwardFlag  = false;
		m_MoveBackwardFlag = false;
	}
	else if(m_MoveBackwardFlag)
	{
			m_Force           -= m_ConstForce*m_Direction;
			m_MoveBackwardFlag = false;
	}

	//sf::Vector2<float> aux = m_Velocity;
	//aux.x *= aux.x * this->m_Mass;
	//aux.y *= aux.y * this->m_Mass;
	//m_Force -= aux;
	//m_Force -= 0.0001f * m_Velocity * Norm(m_Velocity);
	//if( Norm(m_Force) != 0 )
	//	m_Force -= 0.07f * m_Force/Norm(m_Force);

	m_Acceleration = m_Force/m_Mass;

	m_Velocity     += m_Acceleration * elapsedTime;

	m_Velocity     -= 0.00005f * m_Velocity * Norm(m_Velocity);

	//m_Velocity     = m_Acceleration;
	//m_Direction    = m_Velocity*elapsedTime;
	this->m_Sprite.Move(m_Velocity*elapsedTime);

	m_Force.x = 0.0f;
	m_Force.y = 0.0f;

	
}

void PlayerShip::MoveForward()
{
	m_MoveForwardFlag = true;
}

void PlayerShip::MoveBackward()
{
	m_MoveBackwardFlag = true;
}

void PlayerShip::TurnLeft()
{
	m_TurnLeftFlag = true;
}

void PlayerShip::TurnRight()
{
	m_TurnRightFlag = true;
}

void PlayerShip::Shot()
{
	m_pGame->AddObject( new Bullet(m_ShotImage, m_Sprite.GetPosition()+ (m_Direction*m_Sprite.GetSize().x*0.9f), m_Direction, 100.0f) );
}



void PlayerShip::_DrawArrow(sf::RenderWindow& RW, sf::Vector2<float>& Vec, sf::Color color, float scale)
{
	sf::Vector2<float> center = m_Sprite.GetPosition();//+(m_Sprite.GetSize()/2.0f);
	sf::Vector2<float> end    = center+(Vec*scale);
	sf::Shape DirectionVector = sf::Shape::Line(center, end, 2, color, 1.0f, sf::Color::Yellow);
	RW.Draw(DirectionVector);

	float length = Norm(center-end);
	
	sf::Vector3<float> aux = Cross( sf::Vector3<float>(Vec.x,Vec.y,0), sf::Vector3<float>(0,0,1) );
	sf::Vector2<float> left( aux.x, aux.y);
	sf::Vector2<float> invVec = Vec*(-1.0f);
	sf::Vector2<float> diag = (left+invVec)/Norm(left+invVec);

	sf::Shape ArrowLeft = sf::Shape::Line(end, end+diag*(length/8), 2, color, 1.0f, sf::Color::Yellow);
	RW.Draw(ArrowLeft);

	aux = Cross( sf::Vector3<float>(0,0,1) , sf::Vector3<float>(Vec.x,Vec.y,0) );
	sf::Vector2<float> right( aux.x, aux.y);
	diag = (right+invVec)/Norm(right+invVec);

	sf::Shape ArrowRight = sf::Shape::Line(end, end+diag*(length/8), 2, color, 1.0f, sf::Color::Yellow);
	RW.Draw(ArrowRight);
}

void PlayerShip::Draw(sf::RenderWindow& RW)
{
	if( m_DamageOnTick )
	{
		m_Sprite.SetColor(sf::Color(255,0,0, 125));
		m_DamageOnTick = false;
	}else
		m_Sprite.SetColor(sf::Color::White);
	RW.Draw(m_Sprite);
	sf::Shape collisionBound = sf::Shape::Rectangle(m_Bound.Left, m_Bound.Top, m_Bound.Right, m_Bound.Bottom, sf::Color(255,255,255,0), 1, sf::Color::Yellow);
	RW.Draw(collisionBound);
	
	m_Label.SetText("Rojo - Direcion");
	m_Label.SetPosition(0,0);
	RW.Draw(m_Label);
	_DrawArrow(RW, m_Direction, sf::Color::Red, 100.0f);

	m_Label.SetText("Azul - Aceleracion");
	m_Label.SetPosition(0,50);
	RW.Draw(m_Label);
	_DrawArrow(RW, m_Acceleration, sf::Color::Blue);

	m_Label.SetText("Verde - Velocidad");
	m_Label.SetPosition(0,100);
	RW.Draw(m_Label);
	_DrawArrow(RW, m_Velocity, sf::Color::Green);
}

void PlayerShip::ResolveCollision(sf::Vector2<float> normal)
{
	this->m_Force += normal * 5000.0f;
	m_DamageOnTick = true;
}