#include "FollowPlayer3D.h"

FollowPlayer3D::FollowPlayer3D(QCamera * WindowsCam, Player * player)
	: m_camera(WindowsCam)
	, m_player(player)
{
	// Empty
}

void FollowPlayer3D::updateFollowPlayer3D()
{
	QVector3D playerPos = m_player->getPlayerPosition();
	QVector3D cameraPos = m_camera->position();
}
