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
#include <Utils/ModelLoader.h>
#include <QEntity>
#include <QTransform>
#include <QCamera>
#include <QPointLight>
Qt3DCore::QEntity *g_lightEntity = nullptr;
Qt3DRender::QPointLight *g_light = nullptr;
Qt3DCore::QTransform *g_lightTransform = nullptr;

#include "Src/GraphicsDev/Terrain.h"
Terrain *g_terrain = nullptr;
Qt3DCore::QEntity *g_TerrainEntity = nullptr;
Qt3DExtras::QPlaneMesh *g_TerrainMesh = nullptr;

void GameTest::Test()
{
	qWarning("Test Start");

//********************************************************************************
// Root entity********************************************************************
	Qt3DCore::QEntity *rootEntity = m_window3D.getWindowRootEntity();

//*********************************************************************************
// Camera**************************************************************************

	Qt3DRender::QCamera *cameraEntity = m_window3D.camera();

	cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	cameraEntity->setPosition(QVector3D(0, 0, 1.0f));
	cameraEntity->setUpVector(QVector3D(0, 1, 0));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));

//********************************************************************************
// Light ( placed at cameras initial position for 'convenience'*******************
// It can be paced anywhere with setTranslation(QVector3D(x, y, z)****************

	g_lightEntity = new Qt3DCore::QEntity(rootEntity);

	g_light = new Qt3DRender::QPointLight();
	g_light->setColor("white");
	g_light->setIntensity(0.8f);
	g_lightEntity->addComponent(g_light);

	g_lightTransform = new Qt3DCore::QTransform();
	g_lightTransform->setTranslation(cameraEntity->position());
	g_lightEntity->addComponent(g_lightTransform);

//*******************************************************************************
// TERRAIN***********************************************************************

	g_terrain = new Terrain(rootEntity);
	g_TerrainMesh = g_terrain->getPlane();

	Qt3DExtras::QPhongMaterial *TerrainMaterial = new Qt3DExtras::QPhongMaterial();
	TerrainMaterial->setDiffuse(QColor(QRgb(0xff9929)));

	Qt3DCore::QTransform *terrainPosition = new Qt3DCore::QTransform();
	terrainPosition->setTranslation({ 0.0f, 0.0f, -1.0f });
	terrainPosition->setRotationX(90.0f);

	// Terrain
	g_TerrainEntity = new Qt3DCore::QEntity(rootEntity);
	g_TerrainEntity->addComponent(g_TerrainMesh);
	g_TerrainEntity->addComponent(TerrainMaterial);
	g_TerrainEntity->addComponent(terrainPosition);

//*******************************************************************************
	qWarning("Test End");
}

void GameTest::CleanUpAfterTest()
{
	//delete g_testTerrain - deleted by g_terrain;
	delete g_terrain;
	delete g_lightTransform;
	delete g_light;
	delete g_lightEntity;
}
