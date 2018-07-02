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

class HeightMap : public Qt3DCore::QEntity
{
	Q_OBJECT

public:
	explicit HeightMap(QEntity *parent = nullptr);
	~HeightMap();

	void createHeightMap(float mapsideSIZE = 1, int numVerts = 2);

private:
	void vertices();
	void indices();
	void DrawMap();

	QEntity * m_heightMap = nullptr;
	QEntity * m_root = nullptr;

	float SIZE = 1; 
	int VERTEX_COUNT = 2; 
	float *m_vertices = nullptr;
	uint *m_indices = nullptr;
};