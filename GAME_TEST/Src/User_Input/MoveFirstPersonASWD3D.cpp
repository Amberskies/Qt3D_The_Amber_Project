#include "MoveFirstPersonASWD3D.h"
#include <Utils/Input.h>

Move3D::Move3D()
{
	
}

Move3D::~Move3D()
{
	// Empty
}

void Move3D::UpdateMove3D(Window3D &win)
{
	m_cam = win.camera();
	const QVector3D LocalForward(0.0f, 0.0f, -1.0f);
	const QVector3D LocalUp(0.0f, 1.0f, 0.0f);
	const QVector3D LocalRight(1.0f, 0.0f, 0.0f);

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
	//QQuaternion cr = m_cam->

		/*QVector3D translation;
		QVector3D localForward = (m_cam->rotation()).rotatedVector(LocalForward);
		QVector3D localRight = m_cam->rotation().rotatedVector(LocalRight);*/

	//	if (Input::keyPressed(Qt::Key_W))
	//	{
	//		translation += ;
	//	}
	//	if (Input::keyPressed(Qt::Key_S))
	//	{
	//		translation;
	//	}
	//	if (Input::keyPressed(Qt::Key_A))
	//	{
	//		translation;
	//	}
	//	if (Input::keyPressed(Qt::Key_D))
	//	{
	//		translation;
	//	}
	//	if (Input::keyPressed(Qt::Key_Q))
	//	{
	//		translation;
	//	}
	//	if (Input::keyPressed(Qt::Key_E))
	//	{
	//		translation;
	//	}
	//Qt3DRender::QCamera::CameraTranslationOption cto = Qt3DRender::QCamera::TranslateViewCenter;
    //Qt3DRender::QCamera::CameraTranslationOption cto = Qt3DRender::QCamera::DontTranslateViewCenter;
	
	//win.camera()->translate(transSpeed * translation, cto);
}
