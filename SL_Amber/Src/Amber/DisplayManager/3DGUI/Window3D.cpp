#include "Window3D.h"
#include "../UserInput/Input.h"
#include "../../AssetManager/AssetCreator/CustomComponents/FPS_Component/CustomAspect.h"

Window3D::Window3D(QScreen *parent)
	: Qt3DWindow(parent)
{
	
	this->registerAspect(new CustomAspect);

	m_WindowRootEntity = new Qt3DCore::QEntity();
	this->setWidth(400);
	this->setHeight(225);


	qWarning("Window3D Created : User Input events setup");
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
