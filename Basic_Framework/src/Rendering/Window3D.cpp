#include "Window3D.h"
#include "src/Core/Input.h"

Window3D::Window3D(QScreen *parent)
	: Qt3DWindow(parent),
	m_sceneRoot(new Qt3DCore::QEntity)
{
	this->show();
	InitializeWindow3D();
}

Window3D::~Window3D()
{
	this->setRootEntity(nullptr); // Stops the Qt3D engine.
	delete m_lightTransform;
	delete m_light;
	delete m_lightEntity;
	delete m_cameraEntity;
	delete m_sceneRoot;
}

void Window3D::Update()
{
	Input::update();
}



void Window3D::InitializeWindow3D()
{
	m_cameraEntity = this->camera();
	m_cameraEntity->lens()->setPerspectiveProjection(44.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	m_cameraEntity->translate(QVector3D(0.0f, 30.0f, 0.0f));
	m_cameraEntity->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
	m_cameraEntity->setViewCenter(QVector3D(15.0f, 0.5f, 15.0f));

	// Light ( placed at cameras initial position for 'convenience'
	// It can be paced anywhere with setTranslation(QVector3D(x, y, z)
	m_lightEntity = new Qt3DCore::QEntity(m_sceneRoot);
	m_light = new Qt3DRender::QPointLight(m_lightEntity);
	m_light->setColor("white");
	m_light->setIntensity(1);
	m_lightEntity->addComponent(m_light);
	m_lightTransform = new Qt3DCore::QTransform(m_lightEntity);
	m_lightTransform->setTranslation(m_cameraEntity->position());
	m_lightEntity->addComponent(m_lightTransform);
}

// ***** Getters *****

Qt3DRender::QCamera *Window3D::GetCamera()
{
	return m_cameraEntity;
}

Qt3DCore::QEntity * Window3D::GetSceneRoot()
{
	return m_sceneRoot;
}

Qt3DCore::QEntity * Window3D::GetPointLight()
{
	return m_lightEntity;
}

// ***** Setters *****

void Window3D::SetBackgroundColor(QColor color)
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

/*  Notes : */
/*
	********* from previous OpenGL projects *************

void MainWindow::MainUpdate()
{
m_Timer->stop();

/*  // Update input
Input::update();

// Camera Transformation
if (Input::buttonPressed(Qt::RightButton))
{
static const float transSpeed = 0.5f;
static const float rotSpeed   = 0.5f;

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
m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

// Schedule a redraw
QOpenGLWindow::update();

m_Timer->start(10);

}




*/
