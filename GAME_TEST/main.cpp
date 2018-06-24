#include <QGuiApplication>
#include <Window3D.h>

int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);
	Window3D w;
	w.show();
	return a.exec();
}
