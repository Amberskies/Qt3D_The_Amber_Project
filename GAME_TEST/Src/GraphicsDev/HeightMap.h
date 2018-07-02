#pragma once

#include <QObject>
#include <QEntity>
#include <QGeometry>
#include <QBuffer>
#include <QAttribute>
#include <QGeometry>
#include <QGeometryRenderer>
#include <QDiffuseSpecularMaterial>
#include <QTransform>
#include <QVector3D>

struct Vertex3D
{
	QVector3D pos;
	QVector3D nor;
};

class HeightMap : public Qt3DCore::QEntity
{
	Q_OBJECT

public:
	explicit HeightMap(QEntity *parent = nullptr);

	void createHeightMap();

private:
	void vertices();
	void indices();

	void DrawMap();

	Vertex3D *m_vertices = nullptr;
	uint *m_indices = nullptr;

	QEntity * m_heightMap = nullptr;
	QEntity * m_root = nullptr;
	Qt3DRender::QGeometryRenderer *m_mesh = nullptr;
	Qt3DExtras::QDiffuseSpecularMaterial *m_material = nullptr;
	Qt3DCore::QTransform *m_transform = nullptr;
};