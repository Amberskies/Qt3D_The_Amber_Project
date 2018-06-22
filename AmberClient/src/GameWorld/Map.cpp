#include "Map.h"
#include "src/Core/ModelLoader.h"
#include <QTextureMaterial>

Map::Map(Qt3DCore::QEntity *rootEntity) :
	m_rootEntity(rootEntity)
{
	Qt3DRender::QMesh *planeMesh = ModelLoader::LoadMesh("../Assets/Maps/BaseTile.obj");
	Qt3DExtras::QTextureMaterial *planeMaterial = ModelLoader::Texture("../Assets/Maps/grass.png");

	for (float x = 0.0f; x < 30.0f; x++)
	{
		for (float y = 0.0f; y < 30.0f; y++)
		{
			Qt3DCore::QEntity *tile = new Qt3DCore::QEntity(m_rootEntity);
			Qt3DCore::QTransform *planeTransform = new Qt3DCore::QTransform();
			planeTransform->setTranslation(QVector3D(x, 0.0f, y));
			tile->addComponent(planeMesh);
			tile->addComponent(planeMaterial);
			tile->addComponent(planeTransform);
			m_map[int(x)][(int)y] = tile;
		}
	}
}

Map::~Map()
{
	// Empty
}

const int Map::GetMapSizeX()
{
	return m_mapSizeX;
}

const int Map::GetMapSizeY()
{
	return m_mapSizeY;
}
