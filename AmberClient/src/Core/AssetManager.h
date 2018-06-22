#pragma once


class AssetManager
{

public:
	explicit AssetManager();
	virtual ~AssetManager();

	void LoadAssetsFromTextFile();
private:



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