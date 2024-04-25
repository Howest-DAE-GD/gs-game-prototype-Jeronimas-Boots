#pragma once
class Player
{
public:
	Player(const Point2f& pos);
	void Draw(float gridwidth) const;
	Point2f& GetPos();
	void CheckForPickup();
	bool IsAlive();
	int GetScore();
	bool CheckVoid(const Rectf& theVoid, float girdwidth, bool isVoid);
private:
	
	Point2f m_Pos;
	bool m_IsAlive;
	int m_Objects;
	int m_Score;
};

