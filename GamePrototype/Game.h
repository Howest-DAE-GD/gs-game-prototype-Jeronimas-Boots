#pragma once
#include "BaseGame.h"
#include <vector>
#include "Player.h"
#include "Texture.h"
#include "Objects.h"
#include "utils.h"
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	
	Player* m_pPlayer;
	std::vector<bool> m_Void;
	Texture* m_ScoreTxt;
	Texture* m_ObjectCounter;
	Objects* m_Object;
	Point2f m_MousPos;
	

	const float distanceFromBorder{ 100.f };

	float m_Timer{};
	float m_SecondTimer{};
	int m_Cols{ 18 };
	int m_Rows{ 10 };
	bool m_UpKeyDown{ false };
	bool m_DownKey{ false };
	bool m_RighKey{ false };
	bool m_LeftKey{ false };
	std::string m_Score{ };

	const float cellWidth{ GetViewPort().width / m_Cols - distanceFromBorder / m_Cols };
	const float cellHeight{ GetViewPort().height / m_Rows - distanceFromBorder / m_Rows };
	Rectf m_SafeRect;
	int m_Idx;
	Vector2f m_Velocity;
};