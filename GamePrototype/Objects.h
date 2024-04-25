#pragma once
class Objects
{
public:
	Objects(const Point2f& pos);
	void Draw(float gridwidth) const;
private:
	Point2f m_Pos;

};

