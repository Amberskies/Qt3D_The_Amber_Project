#pragma once

#include <QTime>

#include "AssetManager/MapCreator/Terrain.h"
#include "DisplayManager/3DGUI/Window3D.h"
#include "DisplayManager/Camera3D/TheSun.h"
#include "DisplayManager/Camera3D/FollowPlayer3D.h"
#include "Optional/AvatarCreator/Player.h"


class WorldManager : public Qt3DCore::QEntity
{
public:

	explicit WorldManager(class Window3D& window3D, QEntity *parent = nullptr);
	~WorldManager() override;

	void updateWorld();

private:
	
	Window3D & m_win;
	TheSun * m_sunshine = nullptr;
	Terrain *m_terrainTile = nullptr;
	Player * m_player = nullptr;
	FollowPlayer3D *m_camOnPlayer = nullptr;
	QTime m_frameTime;
	float m_deltaTime = 0.0f;

};