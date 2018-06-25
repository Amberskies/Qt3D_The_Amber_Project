#include "Terrain.h"
#include <QTransform>
#include <QDiffuseSpecularMaterial>
#include <QPlaneMesh>

Terrain::Terrain(QEntity *root)
	: m_rootEntity(root)
	, m_terrain(new QEntity(m_rootEntity))
{
	Qt3DExtras::QPlaneMesh *TerrainMesh = new Qt3DExtras::QPlaneMesh();
	TerrainMesh->setMeshResolution(QSize(2, 2));
	
	Qt3DExtras::QDiffuseSpecularMaterial *TerrainMaterial = 
		new Qt3DExtras::QDiffuseSpecularMaterial();
	TerrainMaterial->setDiffuse(QColor(QRgb(0xff9929)));
	
	Qt3DCore::QTransform *terrainPosition = new Qt3DCore::QTransform();
	terrainPosition->setTranslation({ 0.0f, 0.0f, -1.0f });
	terrainPosition->setRotationX(90.0f);

	// Terrain
	m_terrain->addComponent(TerrainMesh);
	m_terrain->addComponent(TerrainMaterial);
	m_terrain->addComponent(terrainPosition);

	qWarning("Terrain Entity Created");
}

Terrain::~Terrain()
{
	delete m_terrain;
	qWarning("Terrain destroyed");
}

Qt3DCore::QEntity * Terrain::getTerrain()
{
	return m_terrain;
}
