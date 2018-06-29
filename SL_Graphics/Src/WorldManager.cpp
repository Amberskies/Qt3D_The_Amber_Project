#include "WorldManager.h"

WorldManager::WorldManager(Window3D& window3D, QEntity *parent)
	: QEntity(parent)
	, m_win(window3D)
	, m_sunshine( new TheSun(m_win.getWindowRootEntity()))
	, m_terraintile(new Terrain(m_win.getWindowRootEntity()))
{
	m_player = new Player(m_win.getWindowRootEntity());
	m_camOnPlayer = new FollowPlayer3D(m_win.camera(), m_player);
	m_frameTime.start();
}

WorldManager::~WorldManager()
{
	delete m_camOnPlayer;
	delete m_player;
	delete m_terraintile;
	delete m_sunshine;
}

void WorldManager::updateWorld()
{
	m_deltaTime = ((float)m_frameTime.elapsed()) / 1000.0f;

	m_player->setDeltaTime(m_deltaTime);
	m_player->updatePlayer();

	m_camOnPlayer->updateFollowPlayer3D();

	m_frameTime.restart();

}

