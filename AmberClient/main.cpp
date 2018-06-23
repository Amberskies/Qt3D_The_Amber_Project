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

/*Notes
Basic framwork setup
Basic Client Log on recognition test use Acount 99 as Admin log on

AssetManager:
	- read/write a formated textFile(later MySQL or Both)
	- load assets specified in text file
	- show example on screen (temporary test) - output to console
	- ??? think about Maps - used for Test code.

***************************************
TODO: 
	

*/