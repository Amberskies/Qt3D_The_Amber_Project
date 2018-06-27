#pragma once

#include <QCamera>
#include "Src/GraphicsDev/Player.h"

class FollowPlayer3D : public Qt3DRender::QCamera
{
public:
	FollowPlayer3D(QCamera *WindowsCam = nullptr, Player *player = nullptr);

	void updateFollowPlayer3D();

private:
	QCamera * m_camera = nullptr;
	Player * m_player = nullptr;

};