#include "HeightMap.h"

#include <QGeometryRenderer>
#include <QBuffer>
#include <QAttribute>
#include <QTransform>
#include <QTexture>

HeightMap::HeightMap(QEntity * parent)
	: QEntity(parent)
	, m_heightMap(new QEntity(parent))
	, m_root(new QEntity(parent))
	, m_material(new Qt3DExtras::QDiffuseSpecularMaterial)
{
	// Empty
}

HeightMap::~HeightMap()
{
	delete m_material;
	delete m_indices;
	delete m_vert;
	delete m_heightMap;
}

void HeightMap::createHeightMap(float mapsideSIZE, int numVerts)
{
	// size of 1 side starts at 0-1
	SIZE = mapsideSIZE;
	// number of vertices down 1 side add 1 as it starts at 0
	VERTEX_COUNT = numVerts;

	qWarning("HeightMap under construction.");
	vertices();
	indices();
	DrawMap();
}

float HeightMap::HeightFromMap(int x, int z, QImage image)
{
	if (x < 0 || x >= image.height() || z <0 || z >= image.height())
	{
		return 0.0f;
	}
	const float MAX_HEIGHT = 50;
	const float MAX_PIXEL_COLOR = 256.0f * 256.0f * 256.0f;

	float height =  (image.pixelColor(QPoint(x, z)).red()) *
					(image.pixelColor(QPoint(x, z)).green()) *
					(image.pixelColor(QPoint(x, z)).blue());
	height /= (MAX_PIXEL_COLOR * 0.5f);
	height *= MAX_HEIGHT;
	height -= (MAX_HEIGHT * 0.25f);
	return height;
}

QVector3D HeightMap::calculateNormal(int x, int z, QImage image)
{
	QVector3D calcNormal = { 0.0f, -1.0f, 0.0f };
	
	float heightL = HeightFromMap(x - 1, z, image);
	float heightR = HeightFromMap(x + 1, z, image);
	float heightD = HeightFromMap(x, z - 1, image);
	float heightU = HeightFromMap(x, z + 1, image);

	calcNormal = { heightL - heightR,
				   2.0f,
				   heightD - heightU };

	calcNormal.normalize();

	return calcNormal;
}

void HeightMap::vertices()
{
	QImage hmap("../Assets/res/heightmap.png");
	//VERTEX_COUNT = hmap->height();
	m_vert = new Vert3D[VERTEX_COUNT * VERTEX_COUNT];
	QVector3D normal = { 0.0f, -1.0f, 0.0f };
	
	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++) 
	{
		for (int j = 0; j < VERTEX_COUNT; j++) 
		{
			m_vert[vertexPointer].verts.setX((float)j / ((float)VERTEX_COUNT - 1) * SIZE);
			m_vert[vertexPointer].verts.setY(HeightFromMap(i, j, hmap));
			m_vert[vertexPointer].verts.setZ((float)i / ((float)VERTEX_COUNT - 1) * SIZE);
			normal = calculateNormal(i, j, hmap);
			m_vert[vertexPointer].norms.setX(normal.x());
			m_vert[vertexPointer].norms.setY(normal.y());
			m_vert[vertexPointer].norms.setZ(normal.z());
			m_vert[vertexPointer].u = (float)j / ((float)VERTEX_COUNT - 1) * VERTEX_COUNT;
			m_vert[vertexPointer].v = (float)i / ((float)VERTEX_COUNT - 1) * VERTEX_COUNT;
			vertexPointer++;
		}
	}
	qDebug() << "Vertices calculated = " << VERTEX_COUNT * VERTEX_COUNT;
}

void HeightMap::indices()
{
	m_indices = new uint[6 * ((VERTEX_COUNT - 1) * (VERTEX_COUNT - 1))];

	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) 
	{
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++)
		{
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			m_indices[pointer++] = topLeft;
			m_indices[pointer++] = bottomLeft;
			m_indices[pointer++] = topRight;
			m_indices[pointer++] = topRight;
			m_indices[pointer++] = bottomLeft;
			m_indices[pointer++] = bottomRight;
		}
	}

}


void HeightMap::loadMaterial()
{
	Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D();
	Qt3DRender::QTextureImage *tex = new Qt3DRender::QTextureImage();
	tex->setSource(QUrl::fromLocalFile("../Assets/res/grassy.png"));
	texture->addTextureImage(tex);
	Qt3DRender::QTextureWrapMode twm(Qt3DRender::QTextureWrapMode::Repeat);
	texture->setWrapMode(twm);
	texture->setGenerateMipMaps(true);
	texture->setSamples(4);

	m_material->setAmbient({ 25, 30, 25, 255 });
	m_material->setDiffuse(QVariant::fromValue(texture));
	m_material->setSpecular(0.01f);
}



void HeightMap::DrawMap()
{
	Qt3DRender::QGeometry *theGeometry = new Qt3DRender::QGeometry;
	theGeometry = makeGeometry();

	Qt3DRender::QGeometryRenderer *mesh = new Qt3DRender::QGeometryRenderer();
	mesh->setGeometry(theGeometry);
	mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
	qWarning("m_mesh (Geometry Renderer Component) now holds all our data.");

	loadMaterial();
	
	Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
	transform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

	m_heightMap->addComponent(mesh);
	m_heightMap->addComponent(m_material);
	m_heightMap->addComponent(transform);
}

Qt3DRender::QGeometry * HeightMap::makeGeometry()
{
	QByteArray VertexBytes, NormalsBytes, UVTexBytes, indexBytes;

	const int num_vertices = (VERTEX_COUNT * VERTEX_COUNT);
	const uint elementSize = 3 + 3 + 2; // 3 floats per position, normals and 2 floats per UV
	const uint stride = elementSize * sizeof(float);

	const int num_Normals = num_vertices;
	const int offset_Normals = 3 * sizeof(float);

	const int num_UVs = 2 * ((VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
	const int offset_UVs = 6 * sizeof(float);

	const int num_indices = 6 * ((VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
	const uint index_element_size = 1; // 1 uint per index

	VertexBytes.resize((elementSize * sizeof(float)) *num_vertices);
	Q_ASSERT(sizeof(int) == sizeof(uint));
	indexBytes.resize((index_element_size * sizeof(uint)) * num_indices);

	memcpy(VertexBytes.data(), reinterpret_cast<const char*>(m_vert), VertexBytes.size());
	memcpy(indexBytes.data(), reinterpret_cast<const char*>(m_indices), indexBytes.size());

	Qt3DRender::QBuffer *VertexBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer));
	Qt3DRender::QBuffer *indexBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer));

	VertexBuffer->setData(VertexBytes);
	indexBuffer->setData(indexBytes);


	Qt3DRender::QAttribute *vertexAttribute = new Qt3DRender::QAttribute(VertexBuffer,
		Qt3DRender::QAttribute::defaultPositionAttributeName(),
		Qt3DRender::QAttribute::Float,
		3, // 3 verts = 1 triangle
		num_vertices,
		0, // offset
		stride,
		0); // node parent if part of a bigger mesh.

	Qt3DRender::QAttribute *normalsAttribute = new Qt3DRender::QAttribute(VertexBuffer,
		Qt3DRender::QAttribute::defaultNormalAttributeName(),
		Qt3DRender::QAttribute::Float,
		3, // 3 normals = 1 triangle
		num_Normals,
		offset_Normals,
		stride,
		0); // node parent if part of a bigger mesh.
		

	qDebug() << "Attribute default Normal Name = " << Qt3DRender::QAttribute::defaultNormalAttributeName();


	Qt3DRender::QAttribute *uvtexAttribute = new Qt3DRender::QAttribute(VertexBuffer,
		Qt3DRender::QAttribute::defaultTextureCoordinateAttributeName(),
		Qt3DRender::QAttribute::Float,
		2, // 2 UV co-ords per square
		num_UVs,
		offset_UVs,
		stride,
		0); // node parent if part of a bigger mesh.


	Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute(indexBuffer,
		Qt3DRender::QAttribute::UnsignedInt,
		index_element_size,
		num_indices,
		0, // offset
		0, // index_stride,
		0); // parent node if part of a bigger object.

	vertexAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
	normalsAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
	uvtexAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
	indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);

	Qt3DRender::QGeometry *geometry = new Qt3DRender::QGeometry;
	geometry->addAttribute(vertexAttribute);
	geometry->addAttribute(normalsAttribute);
	geometry->addAttribute(uvtexAttribute);
	geometry->addAttribute(indexAttribute);

	return geometry;
}


