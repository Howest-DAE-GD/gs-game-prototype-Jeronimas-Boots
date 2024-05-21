#include "pch.h"
#include "Objects.h"
#include "utils.h"

Objects::Objects(const Rectf& pos)
	: m_Pos{rand() % (int)pos.width + pos.left, rand() % (int)pos.height + pos.bottom }
	, m_SpawnRect{pos}
{
}

void Objects::Draw(float gridWidth) const
{
	utils::SetColor(Color4f{ 0.f, 1.f, 0.f, 1.f });
	utils::FillEllipse(m_Pos, (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
}

Point2f Objects::GetPos()
{
	return m_Pos;
}

bool Objects::CheckPickup(const Rectf& platform, const Point2f& playerPos, float cellwidth)
{
	if (utils::IsOverlapping(Circlef(Point2f(playerPos.x + cellwidth / 2, playerPos.y + cellwidth / 2), (cellwidth / 2) - 10.f), Circlef(m_Pos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((playerPos.x + cellwidth / 2) - platform.width, playerPos.y + cellwidth / 2), (cellwidth / 2) - 10.f), Circlef(m_Pos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((playerPos.x + cellwidth / 2) + platform.width, playerPos.y + cellwidth / 2), (cellwidth / 2) - 10.f), Circlef(m_Pos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f(playerPos.x + cellwidth / 2, (playerPos.y + cellwidth / 2) - platform.height), (cellwidth / 2) - 10.f), Circlef(m_Pos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f(playerPos.x + cellwidth / 2, (playerPos.y + cellwidth / 2) + platform.height), (cellwidth / 2) - 10.f), Circlef(m_Pos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((playerPos.x + cellwidth / 2) - platform.width, (playerPos.y + cellwidth / 2) - platform.height), (cellwidth / 2) - 10.f), Circlef(m_Pos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((playerPos.x + cellwidth / 2) - platform.width, (playerPos.y + cellwidth / 2) + platform.height), (cellwidth / 2) - 10.f), Circlef(m_Pos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((playerPos.x + cellwidth / 2) + platform.width, (playerPos.y + cellwidth / 2) + platform.height), (cellwidth / 2) - 10.f), Circlef(m_Pos, (cellwidth / 2) - 10.f))
		|| utils::IsOverlapping(Circlef(Point2f((playerPos.x + cellwidth / 2) + platform.width, (playerPos.y + cellwidth / 2) - platform.height), (cellwidth / 2) - 10.f), Circlef(m_Pos, (cellwidth / 2) - 10.f)))
	{
		m_Pos.x = rand() % (int)m_SpawnRect.width + m_SpawnRect.left;
		m_Pos.y = rand() % (int)m_SpawnRect.height + m_SpawnRect.bottom;
		return true;
	}
	else return false;
}

bool Objects::CheckVoid(const Rectf& theVoid, float gridwidth, bool isVoid)
{
	if (utils::IsPointInRect(m_Pos, theVoid) && isVoid)
	{
		m_Pos.x = rand() % (int)m_SpawnRect.width + m_SpawnRect.left;
		m_Pos.y = rand() % (int)m_SpawnRect.height + m_SpawnRect.bottom;
		return true;
	}
	else return false;
}
