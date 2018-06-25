#include <QGuiApplication>
#include <Window3D.h>

#include "src/GameTest.h"

int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	Window3D w;
	w.show();

	w.setBackgroundColor(QColor(Qt::black));

	GameTest game(w);
	game.Go();

	//start the main event loop ie signals and slots + Input etc.
	// use the quit() slot or exit() to stop the event loop
	int exitCode = a.exec();

	system("PAUSE");
	return exitCode;
}

/* Notes 
Basic Setup to show and close a window complete.

********************************************
TODO:
	...
*/