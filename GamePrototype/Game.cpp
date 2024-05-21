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
	
	m_pPlayer = new Player(Point2f(GetViewPort().width / 2, GetViewPort().height / 2));
	m_Score = std::to_string(000);
	m_ScoreTxt = new Texture("SCORE: " + m_Score, "mine-sweeper.ttf", 20, Color4f{ 1.f, 0.f, 0.f, 1.f });
	int gridSize{ m_Rows * m_Cols};
	for (int i = 0; i < gridSize; i++)
	{
		m_Void.push_back(false);
	}
	Rectf platform{ GetViewPort().width / 2 - cellWidth * m_Cols / 2 + (0 % m_Cols) * cellWidth, 50.f, cellWidth * m_Cols, cellHeight * m_Rows };
	m_Object = new Objects(platform);
	//Point2f(574.444, 360 - cellHeight), 2 * cellWidth, 2 * cellHeight;
	m_SafeRect.left = 574.444f;
	m_SafeRect.bottom = 360 - cellHeight;
	m_SafeRect.width = 2 * cellWidth;
	m_SafeRect.height = 2 * cellHeight;
}

void Game::Cleanup( )
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_ScoreTxt;
	m_ScoreTxt = nullptr;
	delete m_Object;
	m_Object = nullptr;
}

void Game::Update( float elapsedSec )
{
	m_Score = std::to_string(m_pPlayer->GetScore());
	m_Timer += elapsedSec;
	m_SecondTimer += elapsedSec;
	if (m_pPlayer->IsAlive())
	{
		if (m_Timer >= 1.f)
		{
			if (0.9f <= m_SecondTimer && m_SecondTimer <= 1.1f)
			{
				m_Idx = int(rand() % m_Void.size());
				while ((m_Idx == 80 || m_Idx == 81 || m_Idx == 80 + m_Cols || m_Idx == 81 + m_Cols) && !m_Void[m_Idx])
				{
					m_Idx = rand() % m_Void.size();
				}
				m_Timer = 0;
			}
		}
		if (m_SecondTimer >= 2.0f)
		{
			m_SecondTimer = 0;
			m_Void[m_Idx] = true;
		}
		float speed{ 430.f };
		float versnelling{1200.f};
		if (m_LeftKey && m_UpKeyDown || m_UpKeyDown && m_RighKey || m_RighKey && m_DownKey || m_DownKey && m_LeftKey)
		{
			speed /= 1.5f;
		}
		/*else
		{
			m_Velocity.x = speed;
			m_Velocity.y = speed;
		}*/
		if (m_UpKeyDown)
		{
			if (m_Velocity.y <= speed) m_Velocity.y += versnelling * elapsedSec;
		}
		else
		{
			if (-0.001 < m_Velocity.y)
			{
				m_Velocity.y -= 2*versnelling * elapsedSec;
			}
		}
		if (m_DownKey)
		{
			if (m_Velocity.y >= -speed) m_Velocity.y -= versnelling * elapsedSec;
			
		}
		else
		{
			if (0.001 > m_Velocity.y)
			{
				m_Velocity.y += 2*versnelling * elapsedSec;
			}
		}
		if (m_LeftKey)
		{
			if (m_Velocity.x >= -speed) m_Velocity.x -= versnelling * elapsedSec;
		}
		else
		{
			if (0.001 > m_Velocity.x)
			{
				m_Velocity.x += 2*versnelling * elapsedSec;
			}
		}
		if (m_RighKey)
		{
			if (m_Velocity.x <= speed) m_Velocity.x += versnelling * elapsedSec;
		}
		else
		{
			if (-0.001 < m_Velocity.x)
			{
				m_Velocity.x -= 2*versnelling * elapsedSec;
			}
		}
		m_pPlayer->GetPos() += m_Velocity * elapsedSec;
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
	Rectf grid{ };
	grid.height = cellHeight;
	grid.width = cellWidth;

	Rectf platform{ GetViewPort().width / 2 - cellWidth * m_Cols / 2 + (0 % m_Cols) * cellWidth, 50.f, grid.width * m_Cols, grid.height * m_Rows };
	
	if (m_pPlayer->CheckCrafting(platform, m_SafeRect, cellWidth))
	{
		for (int idx{ }; idx < m_Cols * m_Rows; ++idx)
		{
			grid.left = GetViewPort().width / 2 - cellWidth * m_Cols / 2 + (idx % m_Cols) * cellWidth;
			grid.bottom = GetViewPort().height / 2 - cellHeight * m_Rows / 2 + (idx / m_Cols) * cellHeight;
			if (utils::IsPointInRect(m_MousPos, grid) && m_Void[idx] == true)
			{
				m_Void[idx] = false;
				m_pPlayer->IsCrafting();
				delete m_ScoreTxt;
				m_ScoreTxt = nullptr;
				m_ScoreTxt = new Texture("SCORE: " + m_Score, "mine-sweeper.ttf", 20, Color4f{1.f, 0.f, 0.f, 1.f});
			}
		}
	}

	if (m_pPlayer->CheckForPickup(platform, m_Object->GetPos(), cellWidth))
	{
		m_Object->CheckPickup(platform, m_pPlayer->GetPos(), cellWidth);
		delete m_ScoreTxt;
		m_ScoreTxt = nullptr;
		m_ScoreTxt = new Texture("SCORE: " + m_Score, "mine-sweeper.ttf", 20, Color4f{1.f, 0.f, 0.f, 1.f});
	}

	//Rectf platform{ GetViewPort().width / 2 - cellWidth * m_Cols / 2 + (0 % m_Cols) * cellWidth, 50.f, grid.width * m_Cols, grid.height * m_Rows };
	if (m_pPlayer->GetPos().x <= platform.left - platform.width / 2)
	{
		m_pPlayer->GetPos().x = platform.left + platform.width / 2;
	}
	if (m_pPlayer->GetPos().x >= platform.left + platform.width + platform.width / 2)
	{
		m_pPlayer->GetPos().x = platform.left - platform.width / 2;
	}
	if (m_pPlayer->GetPos().y <= platform.bottom - platform.height / 2)
	{
		m_pPlayer->GetPos().y = platform.bottom + platform.height / 2;
	}
	if (m_pPlayer->GetPos().y >= platform.bottom + platform.height + platform.height / 2)
	{
		m_pPlayer->GetPos().y = platform.bottom - platform.height / 2;
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	Rectf grid{ };
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
		if (idx == m_Idx)
		{
			utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
			utils::FillRect(grid);
		}
		if (m_Void[idx])
		{
			utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
			utils::FillRect(grid);
		}
		if (m_pPlayer != nullptr)
		{
			if (m_pPlayer->CheckVoid(platform, grid, grid.width, m_Void[idx]) /*|| !m_pPlayer->CheckVoid(platform, grid.width, true)*/)
			{
				std::cout << "Player fell in void" << std::endl;
			}
		}
		if (m_Object->CheckVoid(grid, grid.width, m_Void[idx]) || m_Object->CheckVoid(m_SafeRect, grid.width, true))
		{
			std::cout << "object fell in void" << std::endl;
		}
	}
	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	utils::DrawRect(m_SafeRect);
	
	m_Object->Draw(cellWidth);
	if (m_pPlayer->IsAlive())
	{
		m_pPlayer->Draw(cellWidth, platform);
	}
	utils::SetColor(Color4f{ 0.6f, 0.7f, 0.8f, 1.0f });
	utils::FillRect(GetViewPort().left, GetViewPort().bottom, GetViewPort().width, platform.bottom);
	utils::FillRect(GetViewPort().left, GetViewPort().bottom, platform.left, GetViewPort().height);
	utils::FillRect(GetViewPort().left, GetViewPort().height - platform.bottom, GetViewPort().width, platform.bottom);
	utils::FillRect(GetViewPort().width - platform.left, GetViewPort().bottom, platform.left, GetViewPort().height);
	if (m_ScoreTxt != nullptr) m_ScoreTxt->Draw(Point2f{ 10.5f, GetViewPort().height - m_ScoreTxt->GetHeight() });
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
	switch (e.keysym.sym)
	{
	case SDLK_a:
		m_LeftKey = true;
		//std::cout << "lelft" << std::endl;
		break;
	case SDLK_d:
		m_RighKey = true;
		//std::cout << "Right " << std::endl;	
		break;
	case SDLK_w:
		m_UpKeyDown = true;
		//std::cout << "Up" << std::endl;
		break;
	case SDLK_s:
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
	case SDLK_a:
		m_LeftKey = false;
		//std::cout << "lelft released" << std::endl;
		break;
	case SDLK_d:
		m_RighKey = false;
		//std::cout << "Right released" << std::endl;
		break;
	case SDLK_w:
		m_UpKeyDown = false;
		//std::cout << "Up released" << std::endl;
		break;
	case SDLK_s:
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
	m_MousPos.x = float(e.x);
	m_MousPos.y = float(e.y);

	
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


