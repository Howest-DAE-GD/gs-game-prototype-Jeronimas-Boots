#pragma once
class Player
{
public:
	Player(const Point2f& pos);
	void Draw(float gridwidth) const;
	void Move(bool Y, int derection);

private:
	
	Point2f m_Pos;

};

