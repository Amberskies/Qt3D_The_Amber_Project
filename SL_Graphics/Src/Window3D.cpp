#include "Window3D.h"
#include "Input.h"

Window3D::Window3D(QScreen *parent)
	: Qt3DWindow(parent)
{
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

// ***** Setters *****

void Window3D::setBackgroundColor(QColor color)
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
