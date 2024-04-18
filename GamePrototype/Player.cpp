#include "pch.h"
#include "Player.h"
#include "utils.h"

Player::Player(const Point2f& pos)
	: m_Pos{pos}
{
}

void Player::Draw(float gridWidth) const
{
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::FillEllipse(Point2f(m_Pos.x + gridWidth / 2, m_Pos.y + gridWidth / 2), (gridWidth / 2) - 10.f, (gridWidth / 2) - 10.f);
}

void Player::Move(bool Y, int direction)
{
}
