#pragma once

#include <QEntity>

class Terrain : public Qt3DCore::QEntity
{
public:
	explicit Terrain(QEntity *root = nullptr);
	 ~Terrain();

	//Get
	Qt3DCore::QEntity * getTerrain();

	//Set

private:
	QEntity * m_rootEntity = nullptr;
	QEntity * m_terrain[100][100];

};