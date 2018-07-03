#pragma once

#include <QObject>
#include <QEntity>
#include <QGeometry>
#include <QVector3D>

class HeightMap : public Qt3DCore::QEntity
{
	Q_OBJECT

public:
	explicit HeightMap(QEntity *parent = nullptr);
	~HeightMap();

	void createHeightMap(float mapsideSIZE = 1, int numVerts = 2);

private:
	struct Vert3D
	{
		QVector3D verts;
		QVector3D norms;
		float u;
		float v;
	};
	Vert3D *m_vert;

	void vertices();
	void indices();
	void DrawMap();
	Qt3DRender::QGeometry * makeGeometry();

	QEntity * m_heightMap = nullptr;
	QEntity * m_root = nullptr;

	float SIZE = 1; 
	int VERTEX_COUNT = 2; 
	uint *m_indices = nullptr;
};