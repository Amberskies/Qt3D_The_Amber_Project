#pragma once

#include <QFile>
#include <QDebug>
#include <QVector>

struct Asset
{
	int id = -1;
	QString name = "";
	QString meshFile = "";
	QString textureFile = "";
};

class AssetManager
{

public:
	explicit AssetManager();
	virtual ~AssetManager();

	void LoadAssetsFromTextFile();
	Asset GetAsset(int i);

private:
	QVector <Asset> m_assets;
};

/*Notes

***************************************
TODO:
AssetManager:
- read/write a formated textFile(later MySQL or Both)
	Lets Assume we creat a .txt useing our fav Text Editor 
	then all we have to do is read it in.


- load assets specified in text file
- show example on screen (temporary test)
- ??? think about Maps ???

*/