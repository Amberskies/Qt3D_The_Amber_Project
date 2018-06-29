#pragma once

#include <QCamera>
#include <QVector3D>

#include "../GAME_TEST/Src/GraphicsDev/Player.h"

class FollowPlayer3D : public Qt3DRender::QCamera
{
public:
	FollowPlayer3D(QCamera *WindowsCam = nullptr, Player *player = nullptr);

	void updateFollowPlayer3D();

private:
	QCamera * m_cameraEntity = nullptr;
	Player * m_player = nullptr;
	QVector3D m_playerPos;
	QVector3D m_cameraPos;
	float m_pitch, m_yaw, m_roll;
	float m_distanceFromPlayer;
	float m_angleAroundPlayer;
};