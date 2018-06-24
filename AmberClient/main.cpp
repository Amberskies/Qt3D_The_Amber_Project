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

	Worked out the size of such a project
	ITS MASSIVE - so......
	its time to split everything up into small chunks.

	- how to use AssetManager in an ECS system
	- considerations for memory management. 
	- as m_assets now contains a list of assets + files required, how to
	use this info efficiently.
	

*/