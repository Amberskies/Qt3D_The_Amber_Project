#include "MoveFirstPersonASWD3D.h"
#include <Utils/Input.h>

Move3D::Move3D()
{
	// Empty
}

Move3D::~Move3D()
{
	// Empty
}

void Move3D::UpdateMove3D(Window3D &win)
{
	// Camera Transformation
	if (Input::buttonPressed(Qt::RightButton))
	{
		static const float transSpeed = 0.5f;
		static const float rotSpeed = 0.5f;

		// Handle rotations
		m_camera.rotate(-rotSpeed * Input::mouseDelta().x(), Camera3D::LocalUp);
		m_camera.rotate(-rotSpeed * Input::mouseDelta().y(), m_camera.right());

		// Handle translations
		QVector3D translation;
		if (Input::keyPressed(Qt::Key_W))
		{
			translation += m_camera.forward();
		}
		if (Input::keyPressed(Qt::Key_S))
		{
			translation -= m_camera.forward();
		}
		if (Input::keyPressed(Qt::Key_A))
		{
			translation -= m_camera.right();
		}
		if (Input::keyPressed(Qt::Key_D))
		{
			translation += m_camera.right();
		}
		if (Input::keyPressed(Qt::Key_Q))
		{
			translation -= m_camera.up();
		}
		if (Input::keyPressed(Qt::Key_E))
		{
			translation += m_camera.up();
		}
		m_camera.translate(transSpeed * translation);
	}

	// Update instance information
	//m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));
}
