#include "Terrain.h"
#include <QDiffuseSpecularMaterial>
#include <QPlaneMesh>
#include <QTextureMaterial>
#include <QTransform>

#include "../SL_Graphics/Src/Utils/ModelLoader.h"

Terrain::Terrain(QEntity *root)
	: QEntity(root)
	, m_rootEntity(root)
{
	Qt3DRender::QMesh *TerrainMesh = ModelLoader::LoadMesh("../Assets/Maps/BaseTile10x10.obj");
	Qt3DExtras::QTextureMaterial *TerrainMaterial = ModelLoader::Texture("../Assets/res/grassy2.png");

	for (float x = 0.0f; x < 100.0f; x += 10.0f)
	{
		for (float z = 0.0f; z < 100.0f; z+= 10.0f)
		{
			m_terrain[(int)x][(int)z] = new Qt3DCore::QEntity(m_rootEntity);
			Qt3DCore::QTransform *TerrainTransform = new Qt3DCore::QTransform();
			TerrainTransform->setTranslation(QVector3D(x, 0.0f, z));

			m_terrain[(int)x][(int)z]->addComponent(TerrainMesh);
			m_terrain[(int)x][(int)z]->addComponent(TerrainMaterial);
			m_terrain[(int)x][(int)z]->addComponent(TerrainTransform);
		}
	}
	qWarning("Terrain Entity Created");
}

Terrain::~Terrain()
{
	qWarning("Terrain destroyed");
}

Qt3DCore::QEntity * Terrain::getTerrain()
{
	return this;
}
