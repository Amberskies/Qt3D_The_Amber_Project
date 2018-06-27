#include "Window3D.h"
#include "Utils/Input.h"
#include "../../GAME_TEST/Src/GraphicsDev/Gui/FPS_Component/CustomAspect.h"

Window3D::Window3D(QScreen *parent)
	: Qt3DWindow(parent)
{
	this->registerAspect(new CustomAspect);

	m_WindowRootEntity = new Qt3DCore::QEntity();
	this->setWidth(400);
	this->setHeight(225);

	Qt3DRender::QCamera *cameraEntity = this->camera();

	cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	cameraEntity->setPosition(QVector3D(0.0f, 0.0f, 0.0f));
	cameraEntity->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
	cameraEntity->setViewCenter(QVector3D(0.0f, 0.0f, -1.0f));
	qWarning("Window3D Created : User Input events setup");
	qWarning("Camera setup : position(0,0,0) looking at -Z into the screen.");
}

Window3D::~Window3D()
{
	qWarning("Window3D Destroyed.");
}

void Window3D::updateWindow3D()
{
	// updates the user input for this window.
	Input::update();
}

// ***** Getters *****

Qt3DCore::QEntity * Window3D::getWindowRootEntity()
{
	return m_WindowRootEntity;
}

void Window3D::setBackgroundColor(QColor color)

// ***** Setters *****

{
	this->defaultFrameGraph()->setClearColor(QColor(color));
}

// ***** Inherited Protected Events *****

void Window3D::mousePressEvent(QMouseEvent *event)
{
	Input::registerMousePress(event->button());
}

void Window3D::mouseReleaseEvent(QMouseEvent *event)
{
	Input::registerMouseRelease(event->button());
}

void Window3D::keyPressEvent(QKeyEvent * event)
{
	if (event->isAutoRepeat())
	{
		event->ignore();
	}
	else
	{
		Input::registerKeyPress(event->key());
	}
}

void Window3D::keyReleaseEvent(QKeyEvent * event)
{
	if (event->isAutoRepeat())
	{
		event->ignore();
	}
	else
	{
		Input::registerKeyRelease(event->key());
	}
}
