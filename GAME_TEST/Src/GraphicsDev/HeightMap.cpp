#include "HeightMap.h"


HeightMap::HeightMap(QEntity * parent)
	: QEntity(parent)
	, m_heightMap(new QEntity(parent))
	, m_root(new QEntity(parent))
{
	// Empty
}

HeightMap::~HeightMap()
{
	delete m_indices;
	delete m_vertices;
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

void HeightMap::vertices()
{

	m_vertices = new float[(VERTEX_COUNT * VERTEX_COUNT) * 3];
	// Position for Vertex 0
	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++) 
	{
		for (int j = 0; j < VERTEX_COUNT; j++) 
		{
			qDebug() << "Pointer = " << vertexPointer;
			m_vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			m_vertices[vertexPointer * 3 + 1] = 0;
			m_vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			vertexPointer++;
		}
	}
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



void HeightMap::DrawMap()
{
	QByteArray VertexBytes, indexBytes;

	const int num_vertices = (VERTEX_COUNT * VERTEX_COUNT); 
 	const uint elementSize = 3; // 3 floats per position
	//const uint stride = elementSize * sizeof(float);

	const int num_indices = 6 * ((VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
	const uint index_element_size = 1; // 1 uint per index
	
	VertexBytes.resize((elementSize * sizeof(float)) *num_vertices);
	Q_ASSERT(sizeof(int) == sizeof(uint));
	indexBytes.resize((index_element_size * sizeof(uint)) * num_indices);

	memcpy(VertexBytes.data(), reinterpret_cast<const char*>(m_vertices), VertexBytes.size());
	memcpy(indexBytes.data(), reinterpret_cast<const char*>(m_indices), indexBytes.size());

	Qt3DRender::QBuffer *vertexBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer));
	Qt3DRender::QBuffer *indexBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer));

	vertexBuffer->setData(VertexBytes);
	indexBuffer->setData(indexBytes);

	
	Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute(vertexBuffer,
		Qt3DRender::QAttribute::defaultPositionAttributeName(),
		Qt3DRender::QAttribute::Float,
		3, // 3 verts = 1 triangle
		num_vertices,
		0, // offset
		0, //stride,
		0); // node parent if part of a bigger mesh.
	
	Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute(indexBuffer,
		Qt3DRender::QAttribute::UnsignedInt,
		index_element_size,
		num_indices,
		0, // offset
		0, // index_stride,
		0); // parent node if part of a bigger object.

	positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
	indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);

	Qt3DRender::QGeometry *geometry = new Qt3DRender::QGeometry;
	geometry->addAttribute(positionAttribute);
	geometry->addAttribute(indexAttribute);

	////////////////////////////////////////////////////////

	Qt3DRender::QGeometryRenderer *m_mesh = new Qt3DRender::QGeometryRenderer();
	m_mesh->setGeometry(geometry);
	m_mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
	qWarning("m_mesh (Geometry Renderer Component) now holds all our data.");

	Qt3DExtras::QDiffuseSpecularMaterial *m_material = new Qt3DExtras::QDiffuseSpecularMaterial();
	m_material->setAmbient(QColor(Qt::red));

	Qt3DCore::QTransform *m_transform = new Qt3DCore::QTransform();
	m_transform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

	m_heightMap->addComponent(m_mesh);
	m_heightMap->addComponent(m_material);
	m_heightMap->addComponent(m_transform);
	///////////////////////////////////////////////////////
}


