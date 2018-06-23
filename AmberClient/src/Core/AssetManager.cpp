#include "AssetManager.h"
#include <QFile>
#include <QDebug>

AssetManager::AssetManager()
{
	// Empty
}

AssetManager::~AssetManager()
{
	// Empty
}

void AssetManager::LoadAssetsFromTextFile()
{
	// Text File Format = Assets.txt and lives in assets folder.
	// we just need  int id, QString Name, QString Mesh and QString Material

	QFile file("../Assets/Assets.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qWarning("file Assets.txt not found.");
		return;
	}
	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		line = line.simplified();

		if (line.startsWith('#')  || line.isEmpty()) continue;
		
		qDebug() << line;

		QStringList temp = line.split(' ');
		int id = temp[0].toInt();
		QString name = temp[1];
		QString meshFile = temp[2];
		QString textureFile = temp[3];
		qDebug() << " ";
		qDebug() << " Id: " << id;
		qDebug() << "Name: " << name;
		qDebug() << "Mesh: " << meshFile;
		qDebug() << "Texture: " << textureFile;
		qDebug() << "************************************";
	}
	file.close();
}
