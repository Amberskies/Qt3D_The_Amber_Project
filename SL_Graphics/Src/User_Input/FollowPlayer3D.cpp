#include "FollowPlayer3D.h"

#include <QtMath>

#include "../SL_Graphics/Src/Utils/Input.h"


FollowPlayer3D::FollowPlayer3D(QCamera * WindowsCam, Player * player)
	: QCamera(WindowsCam)
	, m_player(player)
{
	m_cameraPos = QVector3D(2.0f, 2.0f, 2.5f);
	m_distanceFromPlayer = m_cameraPos.distanceToPoint(m_player->getPlayerPosition());

	this->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	this->setPosition(m_cameraPos);
	this->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
	this->setViewCenter(m_player->getPlayerPosition());

	m_pitch = 45.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_angleAroundPlayer = 45;
}

void FollowPlayer3D::updateFollowPlayer3D()
{
	if (Input::keyPressed(Qt::Key_Q)) m_distanceFromPlayer -= 0.05f;
	if (Input::keyPressed(Qt::Key_E)) m_distanceFromPlayer += 0.05f;

	if (Input::buttonPressed(Qt::RightButton))
	{
		float pitchChange = Input::mouseDelta().y() * 0.1f;
		float angleChange = Input::mouseDelta().x() * 0.3f;

		m_pitch += pitchChange;
		m_angleAroundPlayer -= angleChange;
	}
	
	float hDist = m_distanceFromPlayer * qCos(qDegreesToRadians(m_pitch));
	float vDist = m_distanceFromPlayer * qSin(qDegreesToRadians(m_pitch));

	m_playerPos = m_player->getPlayerPosition();
	float theta = m_player->getRotY() + m_angleAroundPlayer;
	float offsetX = hDist * qSin(qDegreesToRadians(theta));
	float offsetZ = hDist * qCos(qDegreesToRadians(theta));

	m_cameraPos.setX(m_playerPos.x() - offsetX);
	m_cameraPos.setY(m_playerPos.y() + vDist);
	m_cameraPos.setZ(m_playerPos.z() - offsetZ);

	this->setPosition(m_cameraPos);
	this->setViewCenter(m_player->getPlayerPosition());
}
