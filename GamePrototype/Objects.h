#pragma once
class Objects
{
public:
	Objects(const Rectf& pos);
	void Draw(float gridwidth) const;
	Point2f GetPos();
	bool CheckPickup(const Rectf& platform, const Point2f& playerPos, float cellwidth);
	bool CheckVoid(const Rectf& theVoid, float girdwidth, bool isVoid);
private:
	Point2f m_Pos;
	Rectf m_SpawnRect;
};

