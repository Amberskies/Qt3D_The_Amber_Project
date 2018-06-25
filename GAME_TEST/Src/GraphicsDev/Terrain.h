#pragma once

#include <QEntity>
#include <QPlaneMesh>

class Terrain : public Qt3DCore::QEntity
{
public:
	explicit Terrain(QEntity *root = nullptr);
	 ~Terrain();

	//Get
	Qt3DExtras::QPlaneMesh * getPlane();

	//Set

private:
	QEntity * m_rootEntity = nullptr;
	QEntity * m_plane = nullptr;
	Qt3DExtras::QPlaneMesh * m_planeMesh = nullptr;
};