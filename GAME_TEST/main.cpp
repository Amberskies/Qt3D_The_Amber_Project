#include <QGuiApplication>
#include <Window3D.h>

#include "src/GameTest.h"

int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	Window3D w;
	w.show();

	w.setBackgroundColor(QColor(QRgb(0xD100908)));

	GameTest game(w);
	game.Go();

	//start the main event loop ie signals and slots + Input etc.
	// use the quit() slot or exit() to stop the event loop
	int exitCode = a.exec();

	//system("PAUSE");
	return exitCode;
}

/* Notes ***********  https://github.com/Amberskies/Qt3D_The_Amber_Project ****

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
	- sorted :
		I have Left it in a very basic format on purpose
		as anything to do with movement will allways need to be altered later
		usualy at the part in the design phase when the animations are known.

Terrain:
	experimenta; trees ard now working.
	new ideas for height maps being develoed.

	Refactor out all the new files to Static Libs.

	Starting from scratch Draw a line

	Terrain: Test useing a 10x10 grid and make sure it scales up to anything you need.
	then develope into a mesh
	add height values createMap(800, 128) seems to be reasonable
	Trees work 

	looking to create a map around 1km x 1km but takes about an hour to make the map

********************************************
TODO:
	HeightMap stage 2 : add a texture ???
	HeightMap stage 3 : add a heightmap layer
	heightMap stage 4 : dont forget to add normals so it lights up proper.


	Randomize tree placement or develope an asset map ??? Asset Manager
	hmmm.... seems allways to head towards Asset management

	Think about haveing an atlas of maps. - will create a massive open world ie 10 maps x 10map = 8km square Atlas.

	look into seperating it out into map generator as a seperate programe that can save maps to Hard Drive
	time to get us a nice big area with trees on - just to get a feel for things.

	This will lead into better Asset Management
	and aiming for an Atlas of Maps - ooer - (a full Planet maybe ?????)
	- well they did say aim hieght and enjoy whatever results - smiles.
*/