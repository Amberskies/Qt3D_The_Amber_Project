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

	//system("PAUSE");
	return exitCode;
}

/* Notes 
Basic Setup to show and close a window complete.
created a Camera3D and added a Transform3D class to SL_Graphics
- silly me made the OpenGL version - oh well - i'll leave them for later perhaps.
so... 
	User Input created
	 the FPS 3D movement is NOT in its final form
	 this is very basic movement for testing more than anything
	 the 2.5D movement is only usefull when viewing to the SouthEast = +x, +z
		it will also need to be expanded for other viewpoints
so.. we have all we need now to continue and test a Terrain.

Terrain :
	base textured 5x5 flat plain created for tiling.
	Terrain File added
	PlayerFile added
	Camera sorted out at last - its FollowPlayer3D inside UserInput area.

Movement: 
	files are setup
	just the last part of the algorithm to calculate for the camera side
	i think it will then work well with the player movement.

********************************************
TODO:
	Revisit 3D Movement now.
	... Lets get on with Terrain
	This will lead into better Asset Management
	and aiming for an Atlas of Maps - ooer - (a full Planet maybe ?????)
	- well they did say aim hight and enjoy whatever results - smiles.
*/