#include <QtCore/QCoreApplication>
#include "ServerUDP.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ServerUDP server;

	server.Test();

	return a.exec();
}

/*Notes
	Basic framwork setup
	do not use by itself - it has no shutdown or exit feature.
***************************************
TODO: add a shutdown feature

*/