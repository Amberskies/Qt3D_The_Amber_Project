#include "AssetManager.h"


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

	int i = 0;
	while (!in.atEnd())
	{
		QString line = in.readLine();
		line = line.simplified();

		if (line.startsWith('#')  || line.isEmpty()) continue;
		
		QStringList temp = line.split(' ');
		
		Asset a;
		a.id = temp[0].toInt();
		a.name = temp[1];
		a.meshFile = temp[2];
		a.textureFile = temp[3];

		m_assets.push_back(a);
		
		qDebug() << "Id: " << m_assets[i].id;
		qDebug() << "Name: " << m_assets[i].name;
		qDebug() << "Mesh: " << m_assets[i].meshFile;
		qDebug() << "Texture: " << m_assets[i].textureFile;
		qDebug() << "************************************";

		i++;
	}
	file.close();
}

Asset AssetManager::GetAsset(int i)
{
	return m_assets[i];
}


