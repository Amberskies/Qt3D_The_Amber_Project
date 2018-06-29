#include "GameTest.h"
#include <Utils/Input.h>

GameTest::GameTest(Window3D& window3D)
	: m_window3D(window3D)
	, m_worldManager(new WorldManager(m_window3D, m_window3D.getWindowRootEntity()))
{
	// connect the Main Game Loop to a timer.
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(MainGameLoop()));

	qWarning("GameTest : Main Game Loop Created");
}

GameTest::~GameTest()
{
	// Clean up the test mess****************************************
	CleanUpAfterTest();
	//***************************************************************
	delete m_worldManager;
	// Stops the Qt3D Engine
	m_window3D.setRootEntity(nullptr);
	qWarning("TestGame destroyed.");
}

void GameTest::Go()
{
	// Start The Qt3D Engine
	m_window3D.setRootEntity(m_window3D.getWindowRootEntity());

	// set up Test values*******************************************
	//m_frameTime.start();
	//Test();
	//**************************************************************

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
			m_worldManager->updateWorld();


			if (Input::keyPressed(Qt::Key_Escape)) m_gameState =2;

			// Try out some game stuff.*********************************************
			TestGameLoop();
			//**********************************************************************
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

#include "Src/GraphicsDev/Gui/FPS.h"
int g_counter = 0;
FPS *g_fps = nullptr;
bool g_needFPS = true;

void GameTest::TestGameLoop()
{

	if (g_needFPS)
	{
		g_fps = new FPS(m_window3D.getWindowRootEntity());
		g_needFPS = false;
	}


	g_counter++;
	if (g_counter >= 100)
	{
		QString f = QString::number((int)g_fps->getFps());
		f = "Your FPS =  " + f + "    ";
		m_window3D.setTitle(f);

		g_counter = 0;
	}

}

void GameTest::CleanUpAfterTest()
{
	delete g_fps;
}
