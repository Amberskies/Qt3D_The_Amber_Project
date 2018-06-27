#pragma once

#include <QCamera>
#include "Src/GraphicsDev/Player.h"

class FollowPlayer3D : public Qt3DRender::QCamera
{
public:
	FollowPlayer3D(QCamera *WindowsCam = nullptr, Player *player = nullptr);

	void updateFollowPlayer3D();

private:
	float calculateHorizontalDistance();
	float calculateVerticalDistance();
	void calculateCameraPosition(float hDist, float vDist);

private:
	QCamera * m_camera = nullptr;
	Player * m_player = nullptr;
	QVector3D m_playerPos;
	QVector3D m_cameraPos;
	float m_pitch, m_yaw, m_roll;
	float m_distanceFromPlayer;
	float m_angleAroundPlayer;
};