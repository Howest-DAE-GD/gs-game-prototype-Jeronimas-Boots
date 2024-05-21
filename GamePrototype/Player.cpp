#include "pch.h"
#include "Player.h"
#include "utils.h"
#include <iostream>
#include "Texture.h"

Player::Player(const Point2f& pos)
	: m_Pos{ pos }
	, m_IsAlive{ true }
	, m_Objects{ 0 }
	, m_Score{ 0 }
	
{
}

void Player::Draw(float gridWidth, const Rectf& platform) const
{
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::FillEllipse(Point2f(m_Pos.x + gridWidth / 2, m_Pos.y + gridWidth / 2), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
	utils::FillEllipse(Point2f((m_Pos.x + gridWidth / 2) - platform.width, m_Pos.y + gridWidth / 2), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
	utils::FillEllipse(Point2f((m_Pos.x + gridWidth / 2) + platform.width, m_Pos.y + gridWidth / 2), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
	utils::FillEllipse(Point2f(m_Pos.x + gridWidth / 2, (m_Pos.y + gridWidth / 2) + platform.height), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
	utils::FillEllipse(Point2f(m_Pos.x + gridWidth / 2, (m_Pos.y + gridWidth / 2) - platform.height), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
	utils::FillEllipse(Point2f((m_Pos.x + gridWidth / 2) - platform.width, (m_Pos.y + gridWidth / 2) - platform.height), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
	utils::FillEllipse(Point2f((m_Pos.x + gridWidth / 2) - platform.width, (m_Pos.y + gridWidth / 2) + platform.height), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
	utils::FillEllipse(Point2f((m_Pos.x + gridWidth / 2) + platform.width, (m_Pos.y + gridWidth / 2) + platform.height), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
	utils::FillEllipse(Point2f((m_Pos.x + gridWidth / 2) + platform.width, (m_Pos.y + gridWidth / 2) - platform.height), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
}


Point2f& Player::GetPos()
{
	return m_Pos;
}

bool Player::CheckForPickup(const Rectf& platform, const Point2f& pickUpPos, float cellwidth)
{
	if (utils::IsOverlapping(Circlef(Point2f(m_Pos.x + cellwidth / 2, m_Pos.y + cellwidth / 2), (cellwidth / 2) - 10.f), Circlef(pickUpPos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((m_Pos.x + cellwidth / 2) - platform.width, m_Pos.y + cellwidth / 2), (cellwidth / 2) - 10.f), Circlef(pickUpPos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((m_Pos.x + cellwidth / 2) + platform.width, m_Pos.y + cellwidth / 2), (cellwidth / 2) - 10.f), Circlef(pickUpPos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f(m_Pos.x + cellwidth / 2, (m_Pos.y + cellwidth / 2) + platform.height), (cellwidth / 2) - 10.f), Circlef(pickUpPos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f(m_Pos.x + cellwidth / 2, (m_Pos.y + cellwidth / 2) - platform.height), (cellwidth / 2) - 10.f), Circlef(pickUpPos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((m_Pos.x + cellwidth / 2) - platform.width, (m_Pos.y + cellwidth / 2) - platform.height), (cellwidth / 2) - 10.f), Circlef(pickUpPos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((m_Pos.x + cellwidth / 2) - platform.width, (m_Pos.y + cellwidth / 2) + platform.height), (cellwidth / 2) - 10.f), Circlef(pickUpPos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((m_Pos.x + cellwidth / 2) + platform.width, (m_Pos.y + cellwidth / 2) + platform.height), (cellwidth / 2) - 10.f), Circlef(pickUpPos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((m_Pos.x + cellwidth / 2) + platform.width, (m_Pos.y + cellwidth / 2) - platform.height), (cellwidth / 2) - 10.f), Circlef(pickUpPos, (cellwidth / 2) - 10.f)))
	{
		++m_Objects;
		if (m_Objects <= 35)
		{
			m_Score += 10;
		}
		else m_Score += 50;
		std::cout << m_Objects << std::endl;
		return true;
	}
	else return false;
}

bool Player::IsAlive()
{
	return m_IsAlive;
}

int Player::GetScore()
{
	return m_Score;
}

bool Player::CheckVoid(const Rectf& platform, const Rectf& theVoid, float gridwidth, bool isVoid)
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
		if (isVoid && (utils::IsPointInRect(Point2f(m_Pos.x + gridwidth / 2, m_Pos.y + gridwidth / 2), theVoid)
			|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) - platform.width, m_Pos.y + gridwidth / 2), theVoid)
			|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) + platform.width, m_Pos.y + gridwidth / 2), theVoid)
			|| utils::IsPointInRect(Point2f(m_Pos.x + gridwidth / 2, (m_Pos.y + gridwidth / 2) + platform.height), theVoid)
			|| utils::IsPointInRect(Point2f(m_Pos.x + gridwidth / 2, (m_Pos.y + gridwidth / 2) - platform.height), theVoid)
			|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) - platform.width, (m_Pos.y + gridwidth / 2) - platform.height), theVoid)
			|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) - platform.width, (m_Pos.y + gridwidth / 2) + platform.height), theVoid)
			|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) + platform.width, (m_Pos.y + gridwidth / 2) + platform.height), theVoid)
			|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) + platform.width, (m_Pos.y + gridwidth / 2) - platform.height), theVoid)))
		{
			m_IsAlive = false;
			return true;
		}
		else return false;
	}
}

bool Player::CheckCrafting(const Rectf& platform, const Rectf& safeRect, float gridwidth)
{
	if ((utils::IsPointInRect(Point2f(m_Pos.x + gridwidth / 2, m_Pos.y + gridwidth / 2), safeRect)
		|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) - platform.width, m_Pos.y + gridwidth / 2), safeRect)
		|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) + platform.width, m_Pos.y + gridwidth / 2), safeRect)
		|| utils::IsPointInRect(Point2f(m_Pos.x + gridwidth / 2, (m_Pos.y + gridwidth / 2) + platform.height), safeRect)
		|| utils::IsPointInRect(Point2f(m_Pos.x + gridwidth / 2, (m_Pos.y + gridwidth / 2) - platform.height), safeRect)
		|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) - platform.width, (m_Pos.y + gridwidth / 2) - platform.height), safeRect)
		|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) - platform.width, (m_Pos.y + gridwidth / 2) + platform.height), safeRect)
		|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) + platform.width, (m_Pos.y + gridwidth / 2) + platform.height), safeRect)
		|| utils::IsPointInRect(Point2f((m_Pos.x + gridwidth / 2) + platform.width, (m_Pos.y + gridwidth / 2) - platform.height), safeRect)) && m_Objects >= 3)
	{
		return true;
	}
	else return false;
}

void Player::IsCrafting()
{
	m_Objects -= 3;
	std::cout << m_Objects << std::endl;
	m_Score += 10;
}
