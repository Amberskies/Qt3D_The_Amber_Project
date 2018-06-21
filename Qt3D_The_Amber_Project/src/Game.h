#pragma once

#include <QObject>
#include <QTimer>

#include "src/Rendering/Window3D.h"

class Game : public QObject
{
	Q_OBJECT

public:
	Game(class Window3D& window3D);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game();

	void Go();

private:
	void ComposeFrame();
	void UpdateModel();

private slots:
	void MainGameLoop();
	
private:
	Window3D & m_window3D;
	QTimer m_timer;
};
