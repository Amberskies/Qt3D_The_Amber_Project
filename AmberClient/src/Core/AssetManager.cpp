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
		qWarning("file not found");
		return;
	}

	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		qDebug() << line;
	}
}
