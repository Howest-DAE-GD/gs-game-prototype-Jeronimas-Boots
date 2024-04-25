#include "pch.h"
#include "Objects.h"
#include "utils.h"

Objects::Objects(const Point2f& pos)
	: m_Pos{pos}
{
}

void Objects::Draw(float gridWidth) const
{
	utils::SetColor(Color4f{ 0.f, 1.f, 0.f, 1.f });
	utils::FillEllipse(m_Pos, gridWidth / 2, gridWidth / 2);
}
