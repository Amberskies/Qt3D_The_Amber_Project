#include "Terrain.h"
#include <QDiffuseSpecularMaterial>
#include <QPlaneMesh>
#include <QTextureMaterial>
#include <QTransform>
#include <Src/Utils/ModelLoader.h>

Terrain::Terrain(QEntity *root)
	: QEntity(root)
	, m_rootEntity(root)
{
	Qt3DRender::QMesh *TerrainMesh = ModelLoader::LoadMesh("../Assets/Maps/BaseTile10x10.obj");
	Qt3DExtras::QTextureMaterial *TerrainMaterial = ModelLoader::Texture("../Assets/res/grassy2.png");

			m_terrain = new Qt3DCore::QEntity(m_rootEntity);
			Qt3DCore::QTransform *TerrainTransform = new Qt3DCore::QTransform();
			TerrainTransform->setTranslation(QVector3D(0.0f , 0.0f, 0.0f ));

			m_terrain->addComponent(TerrainMesh);
			m_terrain->addComponent(TerrainMaterial);
			m_terrain->addComponent(TerrainTransform);

	qWarning("Terrain Entity Created");
}

Terrain::~Terrain()
{
	delete m_terrain;
	qWarning("Terrain destroyed");
}

Qt3DCore::QEntity * Terrain::getTerrain()
{
	return this;
}
