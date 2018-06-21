#pragma once

#include <Qt3DWindow>
#include <QEntity>
#include <QCamera>
#include <QPointLight>
#include <QTransform>
#include <QForwardRenderer>
#include <QMouseEvent>
#include <QKeyEvent>

class Window3D : public Qt3DExtras::Qt3DWindow
{
private:

	Q_OBJECT

public:
	Window3D(QScreen *parent = nullptr);
	~Window3D();
	void Update();
	void InitializeWindow3D();

	// Gets
	Qt3DRender::QCamera* GetCamera();
	Qt3DCore::QEntity* GetSceneRoot();
	Qt3DCore::QEntity* GetPointLight();
	// Sets
	void SetBackgroundColor(QColor color);

protected:
	// inherited from QWindow.
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
	Qt3DCore::QEntity *m_sceneRoot;
	Qt3DRender::QCamera *m_cameraEntity;
	Qt3DCore::QEntity *m_lightEntity;
	Qt3DRender::QPointLight *m_light;
	Qt3DCore::QTransform *m_lightTransform;
};
