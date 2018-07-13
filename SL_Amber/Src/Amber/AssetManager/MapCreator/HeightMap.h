#pragma once

#include <QObject>
#include <QEntity>
#include <QGeometry>
#include <QDiffuseSpecularMaterial>
#include <QVector3D>
#include <QImage>

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

	float HeightFromMap(int x, int z, QImage image);
	QVector3D calculateNormal(int x, int z, QImage image);
	void vertices();
	void indices();
	void loadMaterial();
	void DrawMap();
	Qt3DRender::QGeometry * makeGeometry();

	QEntity * m_heightMap = nullptr;
	QEntity * m_root = nullptr;
	Qt3DExtras::QDiffuseSpecularMaterial *m_material = nullptr;
	float SIZE = 1; 
	int VERTEX_COUNT = 2; 
	uint *m_indices = nullptr;
};