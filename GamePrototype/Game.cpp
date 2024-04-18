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
	m_Player = new Player(Point2f(GetViewPort().width / 2, GetViewPort().height / 2));
	int gridSize{ rows * cols};
	for (int i = 0; i < gridSize; i++)
	{
		m_Void.push_back(false);
	}
	
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	m_Timer += elapsedSec;

	if (m_Timer >= 5)
	{
		m_Timer = 0;
		m_Void[rand() % m_Void.size()] = true;
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

	Rectf grid{ };
	float distanceFromBorder{ 100.f };
	float cellWidth = GetViewPort().width / cols - distanceFromBorder / cols;
	float cellHeight = GetViewPort().height / rows - distanceFromBorder / rows;
	grid.height = cellHeight;
	grid.width = cellWidth;
	for (int idx{ }; idx < cols * rows; ++idx)
	{
		if (idx == 81 || idx == 82 || idx == 81 + cols || idx == 82 + cols)
		{
			utils::SetColor(Color4f(0.f, 1.f, 1.f, 1.f));
			utils::FillRect(grid);
		}
		grid.left = GetViewPort().width / 2 - cellWidth * cols / 2 + (idx % cols)*cellWidth;
		grid.bottom = GetViewPort().height / 2 - cellHeight * rows / 2 + (idx / cols)*cellHeight;

		utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.f));
		utils::DrawRect(grid);
		if (m_Void[idx])
		{
			utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.f));
			utils::FillRect(grid);
		}
		
	}
	m_Player->Draw(cellWidth);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
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
	glClearColor( 0.0f, 0.0f, 0.f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}


