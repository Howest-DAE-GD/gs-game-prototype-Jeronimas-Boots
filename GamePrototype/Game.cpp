#include "pch.h"
#include "utils.h"
#include "Game.h"
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_ScoreTxt = new Texture(m_Score, "mine-sweeper.ttf", 20, Color4f{ 1.f, 1.f, 1.f, 1.f });
	m_pPlayer = new Player(Point2f(GetViewPort().width / 2, GetViewPort().height / 2));
	int gridSize{ m_Rows * m_Cols};
	for (int i = 0; i < gridSize; i++)
	{
		m_Void.push_back(false);
	}
	//m_Object = new Objects()
}

void Game::Cleanup( )
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_ScoreTxt;
	m_ScoreTxt = nullptr;
}

void Game::Update( float elapsedSec )
{
	m_Timer += elapsedSec;
	if (m_pPlayer->IsAlive())
	{
		if (m_Timer >= 1)
		{
			int idx{ int(rand() % m_Void.size()) };
			m_Timer = 0;
			while ((idx == 80 || idx == 81 || idx == 80 + m_Cols || idx == 81 + m_Cols) && !m_Void[idx])
			{
				idx = rand() % m_Void.size();
			}
			m_Void[idx] = true;	
		}
		if (m_UpKeyDown)
		{
			m_pPlayer->GetPos().y += 230.f * elapsedSec;
		}
		if (m_DownKey)
		{
			m_pPlayer->GetPos().y -= 230.f * elapsedSec;
		}
		if (m_LeftKey)
		{
			m_pPlayer->GetPos().x -= 230.f * elapsedSec;
		}
		if (m_RighKey)
		{
			m_pPlayer->GetPos().x += 230.f * elapsedSec;
		}
	}
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	
	
	m_ScoreTxt->Draw(Point2f{0.5f, GetViewPort().height - m_ScoreTxt->GetHeight()});

	Rectf grid{ };
	float distanceFromBorder{ 100.f };
	float cellWidth = GetViewPort().width / m_Cols - distanceFromBorder / m_Cols;
	float cellHeight = GetViewPort().height / m_Rows - distanceFromBorder / m_Rows;
	grid.height = cellHeight;
	grid.width = cellWidth;

	Rectf platform{ GetViewPort().width / 2 - cellWidth * m_Cols / 2 + (0 % m_Cols) * cellWidth, 50.f, grid.width * m_Cols, grid.height * m_Rows };
	for (int idx{ }; idx < m_Cols * m_Rows; ++idx)
	{
		if (idx == 81 || idx == 82 || idx == 81 + m_Cols || idx == 82 + m_Cols)
		{
			utils::SetColor(Color4f(0.f, 1.f, 1.f, 1.f));
			utils::FillRect(grid);
		}
		grid.left = GetViewPort().width / 2 - cellWidth * m_Cols / 2 + (idx % m_Cols)*cellWidth;
		grid.bottom = GetViewPort().height / 2 - cellHeight * m_Rows / 2 + (idx / m_Cols)*cellHeight;

		utils::SetColor(Color4f(0.8f, 0.8f, 0.8f, 1.f));
		utils::FillRect(grid);
		if (m_Void[idx])
		{
			utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
			utils::FillRect(grid);
		}
		if (m_pPlayer != nullptr)
		{
			if (m_pPlayer->CheckVoid(grid, grid.width, m_Void[idx]) || !m_pPlayer->CheckVoid(platform, grid.width, true))
			{
				std::cout << "Player fell in void" << std::endl;
			}
		}
	}
	if (m_pPlayer->IsAlive())
	{
		m_pPlayer->Draw(cellWidth);
	}
	utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	utils::DrawRect(platform, 4.f);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		m_LeftKey = true;
		//std::cout << "lelft" << std::endl;
		break;
	case SDLK_RIGHT:
		m_RighKey = true;
		//std::cout << "Right " << std::endl;	
		break;
	case SDLK_UP:
		m_UpKeyDown = true;
		//std::cout << "Up" << std::endl;
		break;
	case SDLK_DOWN:
		m_DownKey = true;
		//std::cout << "Down" << std::endl;
		break;
	}
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		m_LeftKey = false;
		//std::cout << "lelft released" << std::endl;
		break;
	case SDLK_RIGHT:
		m_RighKey = false;
		//std::cout << "Right released" << std::endl;
		break;
	case SDLK_UP:
		m_UpKeyDown = false;
		//std::cout << "Up released" << std::endl;
		break;
	case SDLK_DOWN:
		m_DownKey = false;
		//std::cout << "Down released" << std::endl;
		break;
	}
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.6f, 0.7f, 0.8f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}


