#include <QGuiApplication>
#include <Window3D.h>


int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	Window3D w;
	w.show();

	w.setBackgroundColor(QColor(Qt::black));

	//start the main event loop ie signals and slots + Input etc.
	// use quit() to stop the event loop
	int exitCode = a.exec();

	system("PAUSE");
	return exitCode;
}
