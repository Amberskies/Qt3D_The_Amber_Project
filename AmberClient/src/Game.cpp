#include "Game.h"


Game::Game(Window3D & window3D) :
	m_window3D(window3D)
	, m_gfx(new Graphics(window3D))
{
	// Take the root from the main window and give it to the Graphics
	m_gfx->SetRoot(m_window3D.GetSceneRoot());
	
	m_gfx->CreatePlayer();
	m_gfx->CreateMap();

	// connect the main Game Loop
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(MainGameLoop()));
}

Game::~Game()
{
	delete m_gfx;
}

void Game::Go()
{
	// setRootEntity starts the Qt3D engine.
	m_window3D.setRootEntity(m_window3D.GetSceneRoot());
	m_timer.start(10);
}

void Game::MainGameLoop()
{
	m_timer.stop();

	if (m_window3D.isExposed())
	{
		UpdateModel();
		ComposeFrame();
	}
	
	m_timer.start(10);
}

void Game::ComposeFrame()
{
	// Empty
}

void Game::UpdateModel()
{
	m_window3D.Update(); // Updates user input to the Window
	m_gfx->UpdateGraphics();
}
