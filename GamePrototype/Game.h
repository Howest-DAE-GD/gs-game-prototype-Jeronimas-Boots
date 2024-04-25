#pragma once
#include "BaseGame.h"
#include <vector>
#include "Player.h"
#include "Texture.h"
#include "Objects.h"
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
	Objects* m_Object;

	float m_Timer{};
	int m_Cols{ 18 };
	int m_Rows{ 10 };
	bool m_UpKeyDown{ false };
	bool m_DownKey{ false };
	bool m_RighKey{ false };
	bool m_LeftKey{ false };
	std::string m_Score{ std::to_string(m_Timer) };
};