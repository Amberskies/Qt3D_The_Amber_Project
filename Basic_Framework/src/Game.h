#pragma once

#include <QObject>
#include <QTimer>

#include "src/Rendering/Window3D.h"
#include "src/Rendering/Graphics.h"




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
	/********************************/
	/*  User Functions              */

private slots:
	void MainGameLoop();
	
	/********************************/
private:
	/********************************/
	/*  User Variables              */
	Window3D & m_window3D;
	Graphics *m_gfx;
	QTimer m_timer;

	/********************************/
};
