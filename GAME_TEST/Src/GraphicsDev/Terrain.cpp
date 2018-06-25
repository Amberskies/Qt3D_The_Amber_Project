#include "Terrain.h"

Terrain::Terrain(QEntity *root)
	: m_rootEntity(root)
	, m_plane     (new QEntity(m_rootEntity))
	, m_planeMesh (new Qt3DExtras::QPlaneMesh())
{
	qWarning("Terrain Entity Created");
}

Terrain::~Terrain()
{
	delete m_plane;
	qWarning("Terrain destroyed");
}

Qt3DExtras::QPlaneMesh * Terrain::getPlane()
{
	m_planeMesh->setWidth(0.5f);
	m_planeMesh->setHeight(0.5f);
	return m_planeMesh;
}
