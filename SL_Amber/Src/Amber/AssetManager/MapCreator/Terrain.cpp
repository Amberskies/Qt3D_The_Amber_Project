#include "Terrain.h"

#include <QTransform>
#include "../LoadData/ModelLoader.h"

Terrain::Terrain(QEntity *root)
	: QEntity(root)
{
	m_TerrainMesh = ModelLoader::LoadMesh("../Assets/Maps/BaseTile10x10.obj");
	m_TerrainMaterial = ModelLoader::Texture("../Assets/res/grassy2.png");
	qWarning("Terrain Entity Created");
}

Terrain::~Terrain()
{
//	delete [] m_terrain;
	qWarning("Terrain destroyed");
}

void Terrain::createTerrainTile(int index,QVector3D location)
{
	m_terrain[index] = new Qt3DCore::QEntity(this);
	Qt3DCore::QTransform *TerrainTransform = new Qt3DCore::QTransform();
	TerrainTransform->setTranslation(location);

	m_terrain[index]->addComponent(m_TerrainMesh);
	m_terrain[index]->addComponent(m_TerrainMaterial);
	m_terrain[index]->addComponent(TerrainTransform);
}

Qt3DCore::QEntity * Terrain::getTerrain()
{
	return this;
}
