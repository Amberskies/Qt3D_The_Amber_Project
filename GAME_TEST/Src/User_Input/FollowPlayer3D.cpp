#include "FollowPlayer3D.h"
#include <Utils/Input.h>
#include <QtMath>

FollowPlayer3D::FollowPlayer3D(QCamera * WindowsCam, Player * player)
	: m_camera(WindowsCam)
	, m_player(player)
{
	m_playerPos = m_player->getPlayerPosition();
	m_cameraPos = m_camera->position();

	m_pitch = 20.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_distanceFromPlayer = (player->getPlayerPosition()).distanceToPoint(m_camera->position());
	m_angleAroundPlayer = 0;
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
	
	float horizontalDistance = calculateHorizontalDistance();
	float verticalDistance = calculateVerticalDistance();
	calculateCameraPosition(horizontalDistance, verticalDistance);

}

float FollowPlayer3D::calculateHorizontalDistance()
{
	return m_distanceFromPlayer * qCos(qDegreesToRadians(m_pitch));
}

float FollowPlayer3D::calculateVerticalDistance()
{
	return m_distanceFromPlayer * qSin(qDegreesToRadians(m_pitch));
	;
}

void FollowPlayer3D::calculateCameraPosition(float hDist, float vDist)
{
	float theta = m_player->getRotY() + m_angleAroundPlayer;
	float offsetX = hDist * qSin(qDegreesToRadians(theta));
	float offsetZ = hDist * qCos(qDegreesToRadians(theta));

	m_cameraPos.setX(m_playerPos.x() - offsetX);
	m_cameraPos.setY(m_playerPos.y()+ vDist);
	m_cameraPos.setZ(m_playerPos.z() - offsetZ);
	
	m_camera->setPosition(m_cameraPos);
	m_camera->setViewCenter(m_playerPos);
}
