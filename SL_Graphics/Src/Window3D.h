#pragma once
#include <Qt3DWindow>
#include <QEntity>
#include <QForwardRenderer>
#include <QMouseEvent>
#include <QKeyEvent>

class Window3D : public Qt3DExtras::Qt3DWindow
{
public:
	Window3D(QScreen *parent = nullptr);
	~Window3D();

	void updateWindow3D();

	//Get
	Qt3DCore::QEntity* getWindowRootEntity();
	//Set
	void setBackgroundColor(QColor color);

protected:
	// inherited from QWindow.
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
	Qt3DCore::QEntity *m_WindowRootEntity = nullptr;
};
