#pragma once
class Texture;
class Player
{
public:
	Player(const Point2f& pos);
	void Draw(float gridwidth, const Rectf& platform) const;
	Point2f& GetPos();
	bool CheckForPickup(const Rectf& platform, const Point2f& pickUpPos, float cellwidth);
	bool IsAlive();
	int GetScore();
	bool CheckVoid(const Rectf& platform, const Rectf& theVoid, float girdwidth, bool isVoid);
	bool CheckCrafting(const Rectf& platform, const Rectf& safeRect, float gridwidth);
	void IsCrafting();
private:
	
	Point2f m_Pos;
	bool m_IsAlive;
	int m_Objects;
	int m_Score;
	
};

