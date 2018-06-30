#pragma once

#include <QEntity>
#include <QMesh>
#include <QTextureMaterial>

class Terrain : public Qt3DCore::QEntity
{
public:
	explicit Terrain(QEntity *root = nullptr);
	 ~Terrain();

	 void createTerrainTile(int index, QVector3D location);
	//Get
	Qt3DCore::QEntity * getTerrain();

	//Set

private:
	QEntity * m_terrain[100];
	Qt3DRender::QMesh *m_TerrainMesh = nullptr;
	Qt3DExtras::QTextureMaterial *m_TerrainMaterial = nullptr;
};