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
	// Clean up the test mess****************************************
	CleanUpAfterTest();
	//***************************************************************

	// Stops the Qt3D Engine
	m_window3D.setRootEntity(nullptr);
	qWarning("TestGame destroyed.");
}

void GameTest::Go()
{
	// Start The Qt3D Engine
	m_window3D.setRootEntity(m_window3D.getWindowRootEntity());

	// set up Test values*******************************************
	m_frameTime.start();
	Test();
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
#include <QCamera>

#include "Src/Lighting/TheSun.h"
TheSun *g_sunshine = nullptr;
#include "Src/GraphicsDev/Terrain.h"
Terrain *g_terraintile = nullptr;
#include "Src/GraphicsDev/Player.h"
Player * g_player = nullptr;
#include "Src/User_Input/FollowPlayer3D.h"
FollowPlayer3D *g_camOnPlayer;

void GameTest::Test()
{
	qWarning("Test Start");

//********************************************************************************
// Root entity********************************************************************
	Qt3DCore::QEntity *rootEntity = m_window3D.getWindowRootEntity();

//********************************************************************************
	g_sunshine = new TheSun(rootEntity);
//********************************************************************************
// TERRAIN************************************************************************
	g_terraintile = new Terrain(rootEntity);
// Player*************************************************************************
	g_player = new Player(rootEntity);
	g_camOnPlayer = new FollowPlayer3D(m_window3D.camera(), g_player);
//********************************************************************************
	
	qWarning("Test End : Next will be The TestGameLoop.");
}

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

	g_camOnPlayer->updateFollowPlayer3D();

	g_counter++;
	if (g_counter >= 100)
	{
		QString f = QString::number((int)g_fps->getFps());
		f = "Your FPS =  " + f + "    ";
		m_window3D.setTitle(f);

		g_counter = 0;
	}

	m_deltaTime = ((float) m_frameTime.elapsed()) / 1000.0f;
	g_player->setDeltaTime(m_deltaTime);
	g_player->updatePlayer();
	m_frameTime.restart();
}

void GameTest::CleanUpAfterTest()
{
	delete g_camOnPlayer;
	delete g_fps;
	delete g_player;
	delete g_terraintile;
	delete g_sunshine;
}
