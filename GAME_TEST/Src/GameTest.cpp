#include "GameTest.h"
#include <Amber/DisplayManager/UserInput/Input.h>

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
	// set up Test values*******************************************
	Test();
	m_frameTime.start();
	
	//**************************************************************


	// Start The Qt3D Engine
	m_window3D.setRootEntity(m_window3D.getWindowRootEntity());


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
#include <Amber/AssetManager/AssetCreator/Tree.h>
Tree *g_tree = nullptr;


// switching terrain Generation off for this test //
#include <Amber/AssetManager/MapCreator/HeightMap.h>
HeightMap *g_map;
// switching terrain Generation off for this test //


void GameTest::Test()
{
	Qt3DCore::QEntity *root = m_window3D.getWindowRootEntity();

	/////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////

	g_map = new HeightMap(root);
	g_map->createHeightMap(500.0f, 64); // 800.0f x 128 seems a good size

	/////////////////////////////////////////////////////////

	g_tree = new Tree(root);
	g_tree->createTree(0, QVector3D(4.0f, -0.09f, 6.0f));
	g_tree->createTree(1, QVector3D(5.0f, -0.09f, 7.0f));

}

#include <Amber/AssetManager/AssetCreator/CustomComponents/FPS.h>
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
	delete g_tree;
	delete g_map;
}
