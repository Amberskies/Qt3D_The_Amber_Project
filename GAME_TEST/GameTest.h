#pragma once

#include <QObject>
#include <QTimer>
#include <Window3D.h>

class GameTest : public QObject
{
	Q_OBJECT

public:
	GameTest(class Window3D& window3D);
	~GameTest();

	void Go();

private slots:
	void MainGameLoop();

private:
	Window3D & m_window3D;
	QTimer m_timer;
};
