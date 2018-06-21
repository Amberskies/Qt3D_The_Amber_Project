#include <QGuiApplication>
#include "src/Rendering/Window3D.h"
#include "src/Game.h"


int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	Window3D wnd;
	wnd.SetBackgroundColor(Qt::darkBlue);

	Game myGame(wnd);
	myGame.Go();

	return a.exec();
}

// Notes : 
/*
	
	*/
