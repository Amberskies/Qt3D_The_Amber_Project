#include "FollowPlayer3D.h"

#include <Src/Utils/Input.h>
#include <QtMath>


FollowPlayer3D::FollowPlayer3D(QCamera * WindowsCam, Player * player)
	: m_cameraEntity(WindowsCam)
	, m_player(player)
{
	//m_cameraPos = QVector3D(0.0f, 0.0f, 0.0f);

	m_cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	m_cameraEntity->setPosition(m_cameraPos);
	m_cameraEntity->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
	m_cameraEntity->setViewCenter(m_player->getPlayerPosition());

	m_pitch = 15.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_distanceFromPlayer = 5.0f;
	//m_distanceFromPlayer = m_cameraPos.distanceToPoint(m_player->getPlayerPosition());
	m_angleAroundPlayer =180;
	qWarning("Camera following player created.");
}

FollowPlayer3D::~FollowPlayer3D()
{
	// Empty
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

	m_cameraEntity->setPosition(m_cameraPos);
	m_cameraEntity->setViewCenter(m_player->getPlayerPosition());
}
