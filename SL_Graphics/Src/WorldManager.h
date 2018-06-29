#pragma once

#include <QTime>

#include "./Window3D.h"
#include "../GAME_TEST/Src/Lighting/TheSun.h"
#include "../GAME_TEST/Src/GraphicsDev/Terrain.h"
#include "../GAME_TEST/Src/GraphicsDev/Player.h"
#include "../GAME_TEST/Src/User_Input/FollowPlayer3D.h"


class WorldManager : public Qt3DCore::QEntity
{
public:

	explicit WorldManager(class Window3D& window3D, QEntity *parent = nullptr);
	~WorldManager() override;

	void updateWorld();

private:
	
	Window3D & m_win;
	TheSun * m_sunshine = nullptr;
	Terrain *m_terraintile = nullptr;
	Player * m_player = nullptr;
	FollowPlayer3D *m_camOnPlayer = nullptr;
	QTime m_frameTime;
	float m_deltaTime = 0.0f;

};