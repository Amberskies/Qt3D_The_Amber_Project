#include "GameTest.h"
#include <Input.h>

GameTest::GameTest(Window3D& window3D)
	: m_window3D(window3D)
{
	// connect the Main Game Loop to a timer.
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(MainGameLoop()));

	qWarning("GameTest : Main Game Loop Created");
}

GameTest::~GameTest()
{
	qWarning("TestGame desttroyed.");
}

void GameTest::Go()
{
	// start the Main Game Loop event timer.
	m_timer.start(10);
}

void GameTest::MainGameLoop()
{
	m_timer.stop();

	if (m_window3D.isExposed())
	{
		// Update user input to the Window
		m_window3D.updateWindow3D();
		if (Input::keyPressed(Qt::Key_Escape)) exit(0);
	}

	m_timer.start(10);
}
