#pragma once

#include <QEntity>

#include "src/GameWorld/Player.h"
#include "src/GameWorld/Map.h"
#include "src/Rendering/Window3D.h"
#include "src/Physx/MovePlayer.h"

class Graphics
{
public:
	Graphics(class Window3D& window3D);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();

	void CreatePlayer();
	void CreateMap();

	void UpdateGraphics();

	// Gets

	// Sets
	void SetRoot(Qt3DCore::QEntity *rootEntity);

private:
	Qt3DCore::QEntity *m_rootEntity = nullptr;
	Qt3DCore::QEntity *m_entity = nullptr;
	Player *m_player = nullptr;
	Map *m_map = nullptr;
	Window3D& m_wnd;
	MovePlayer m_movePlayer;
	bool m_playerMoving;
};
