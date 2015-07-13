#include "Object.h"

sf::Vector2<float> Object::GetPosition()
{
	return m_Sprite.GetPosition();
}

bool Object::Collide(Object& A, Object& B)
	{
		float midA = (A.m_Bound.Left + A.m_Bound.Right)/2;
		float midB = (B.m_Bound.Left + B.m_Bound.Right)/2;

		if( !(abs(midA - midB) < (A.m_Bound.GetWidth()/2.0f+B.m_Bound.GetWidth()/2.0f)) )
			return false;

		midA = (A.m_Bound.Top + A.m_Bound.Bottom)/2;
		midB = (B.m_Bound.Top + B.m_Bound.Bottom)/2;

		if( !(abs(midA - midB) < (A.m_Bound.GetHeight()/2.0f+B.m_Bound.GetHeight()/2.0f)) )
			return false;

		return true;
	}