#include "Game.h"

Game::Game(Window3D & window3D) :
	m_window3D(window3D)
{
	// connect the main Game Loop
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(MainGameLoop()));
}

Game::~Game()
{
	// Empty
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

void Game::UpdateModel()
{
	// Update user input to the Window
	m_window3D.Update(); 
}

void Game::ComposeFrame()
{
	// Empty
}

