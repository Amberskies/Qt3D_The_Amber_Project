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
	static const float transSpeed = 0.05f;
	static const float rotSpeed = 0.1f;

	// Camera Transformation
	if (Input::buttonPressed(Qt::RightButton))
	{
		// Handle rotations
		float dx = Input::mouseDelta().x();
		float dy = Input::mouseDelta().y();

		//qDebug() <<
			win.camera()->pan(Input::mouseDelta().x() * rotSpeed);
			win.camera()->tilt(Input::mouseDelta().y() * -rotSpeed);
	}
		// Handle translations
		QVector3D translation;
		if (Input::keyPressed(Qt::Key_W))
		{
			translation -= m_camera.forward();
		}
		if (Input::keyPressed(Qt::Key_S))
		{
			translation += m_camera.forward();
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
	Qt3DRender::QCamera::CameraTranslationOption cto = Qt3DRender::QCamera::TranslateViewCenter;
  //Qt3DRender::QCamera::CameraTranslationOption cto = Qt3DRender::QCamera::DontTranslateViewCenter;
	
	win.camera()->translate(transSpeed * translation, cto);
}
