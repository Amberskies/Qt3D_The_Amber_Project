#include "GameTest.h"
#include <Utils/Input.h>

GameTest::GameTest(Window3D& window3D)
	: m_window3D(window3D)
{
	// connect the Main Game Loop to a timer.
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(MainGameLoop()));

	qWarning("GameTest : Main Game Loop Created");
}

GameTest::~GameTest()
{
	CleanUpAfterTest();
	// Stops the Qt3D Engine
	m_window3D.setRootEntity(nullptr);
	qWarning("TestGame destroyed.");
}

void GameTest::Go()
{
	// Start The Qt3D Engine
	m_window3D.setRootEntity(m_window3D.getWindowRootEntity());
	Test();
	// start the Main Game Loop event timer.
	m_timer.start(10);
}

void GameTest::MainGameLoop()
{
	m_timer.stop();

	if (m_window3D.isExposed())
	{
		

		if (m_gameState == 0)
		{
			//m_window3D.Update();
			//if (Input::keyPressed(Qt::Key_Return))
			//{
			//	m_startScreen->RemoveStart();
				m_gameState = 1;
			//}
		}
		else if (m_gameState == 1)
		{
			// Update user input to the Window
			m_window3D.updateWindow3D();
			if (Input::keyPressed(Qt::Key_Escape)) m_gameState =2;
		}
		else if (m_gameState == 2)
		{
			//m_EndScreen->GameOver(m_gfx->GetPlayer()->GetPlayerPosition());

			//m_window3D.Update();
			//if (Input::keyPressed(Qt::Key_Return))
			//{
				exit(0);
			//}
		}
		else
		{
			qWarning("m_gameState went out of bounds.");
		}
	}

	m_timer.start(10);
}
// ************************************
// *********** Test Area **************
//*************************************
#include <QCamera>

#include "Src/Lighting/TheSun.h"
TheSun *g_sunshine = nullptr;
#include "Src/GraphicsDev/Terrain.h"
Terrain *g_terrain = nullptr;

void GameTest::Test()
{
	qWarning("Test Start");

//********************************************************************************
// Root entity********************************************************************
	Qt3DCore::QEntity *rootEntity = m_window3D.getWindowRootEntity();

//*********************************************************************************
// Camera****Moved to Window3D*****************************************************

	

//********************************************************************************
// *******************************************************************************
	g_sunshine = new TheSun(rootEntity);
//********************************************************************************
// TERRAIN************************************************************************
	g_terrain = new Terrain(rootEntity);
//********************************************************************************
	qWarning("Test End");
}

void GameTest::CleanUpAfterTest()
{
	delete g_terrain;
	delete g_sunshine;
}
