#include "pch.h"
#include "Player.h"
#include "utils.h"
#include <iostream>

Player::Player(const Point2f& pos)
	: m_Pos{ pos }
	, m_IsAlive{ true }
	, m_Objects{ 0 }
	, m_Score{ 0 }
{
}

void Player::Draw(float gridWidth) const
{
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::FillEllipse(Point2f(m_Pos.x + gridWidth / 2, m_Pos.y + gridWidth / 2), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
}


Point2f& Player::GetPos()
{
	return m_Pos;
}

void Player::CheckForPickup()
{
	++m_Objects;
	m_Score += 10;
}

bool Player::IsAlive()
{
	return m_IsAlive;
}

int Player::GetScore()
{
	return m_Score;
}

bool Player::CheckVoid(const Rectf& theVoid, float gridwidth, bool isVoid)
{
	/*std::cout << "Bottom left {" << theVoid.left << ", " << theVoid.bottom << "}, ";
	std::cout << "Width: " << theVoid.width << ", Height: " << theVoid.height << std::endl;*/
	if (theVoid.width > gridwidth)
	{
		if (utils::IsPointInRect(Point2f(m_Pos.x + gridwidth / 2, m_Pos.y + gridwidth / 2), theVoid) && isVoid)
		{
			return true;
		}
		else
		{
			m_IsAlive = false;
			return false;
		}
	}
	else
	{
		if (utils::IsPointInRect(Point2f(m_Pos.x + gridwidth / 2, m_Pos.y + gridwidth / 2), theVoid) && isVoid)
		{
			m_IsAlive = false;
			return true;
		}
		else return false;
	}
	
}
