#pragma once

#include <QEntity>

#include <QPlaneMesh>
#include <QDiffuseSpecularMaterial>
#include <QTransform>

#include <QGeometry>
#include <QVector3D>


class HeightMap : public Qt3DCore::QEntity, public Qt3DExtras::QPlaneMesh
{
public:
	explicit HeightMap(QEntity *parent = nullptr);

	void createHeightMap();

private:
	void calcHeight();
	void DrawLine();

	QEntity * m_heightMap = nullptr;
	QEntity * m_root = nullptr;
	QPlaneMesh *m_mesh = nullptr;
	Qt3DExtras::QDiffuseSpecularMaterial *m_material = nullptr;
	Qt3DCore::QTransform *m_transform = nullptr;
	Qt3DRender::QGeometry *m_currentMap = nullptr;
};