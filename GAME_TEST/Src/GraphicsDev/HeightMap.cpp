#include "HeightMap.h"


HeightMap::HeightMap(QEntity * parent)
	: QEntity(parent)
	, m_heightMap(new QEntity(parent))
	, m_root(new QEntity(parent))
{

}

void HeightMap::createHeightMap()
{
	qWarning("HeightMap under construction.");
	vertices();
	indices();
	DrawMap();
}

void HeightMap::vertices()
{
	const int num_verts = 3;
	m_vertices = new Vertex3D [num_verts];
	// Position for Vertex 0
	m_vertices[0].pos = { 0.0f, 0.0f, 0.0f };
	// Normal for Vertex 0
	m_vertices[0].nor = { 0.0f, 1.0f, 0.0f };

	// Position for Vertex 1
	m_vertices[1].pos = { 0.0f, 0.0f, 1.0f };
	// Normal for Vertex 1
	m_vertices[1].nor = { 0.0f, 1.0f, 0.0f };

	// Position for Vertex 2
	m_vertices[2].pos = { 1.0f, 0.0f, 0.0f };
	// Normal for Vertex 2
	m_vertices[2].nor = { 0.0f, 1.0f, 0.0f };

}

void HeightMap::indices()
{
	const int num_inds = 3;
	m_indices = new uint[num_inds];

	int ix = 0;

	m_indices[ix++] = 0;
	m_indices[ix++] = 1;
	m_indices[ix++] = 2;

}



void HeightMap::DrawMap()
{
	QByteArray VertexBytes, indexBytes;

	const int num_vertices = 3; // 
 	const quint32 elementSize = 3 + 3; // 3 for position, 3 for normal
	const quint32 stride = elementSize * sizeof(float);

	const int num_indices = 3;
	const uint index_element_size = 1; // 1 number per index
	
	VertexBytes.resize(stride *num_vertices);
	Q_ASSERT(sizeof(int) == sizeof(uint));
	indexBytes.resize(num_indices * sizeof(uint));

	memcpy(VertexBytes.data(), reinterpret_cast<const char*>(m_vertices), VertexBytes.size());
	memcpy(indexBytes.data(), reinterpret_cast<const char*>(m_indices), indexBytes.size());

	Qt3DRender::QBuffer *vertexBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer));
	Qt3DRender::QBuffer *indexBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer));

	vertexBuffer->setData(VertexBytes);
	indexBuffer->setData(indexBytes);

	
	Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute(buf,
		Qt3DRender::QAttribute::defaultPositionAttributeName(),
		Qt3DRender::QAttribute::Float,
		3, // 3 verts = 1 triangle
		num_vertices,
		0, // offset
		stride,
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

	m_mesh = new Qt3DRender::QGeometryRenderer();
	m_mesh->setGeometry(geometry);
	m_mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
	qWarning("m_mesh (Geometry Renderer Component) now holds all our data.");

	m_material = new Qt3DExtras::QDiffuseSpecularMaterial();
	m_material->setAmbient(QColor(Qt::red));

	m_transform = new Qt3DCore::QTransform();
	m_transform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

	m_heightMap->addComponent(m_mesh);
	m_heightMap->addComponent(m_material);
	m_heightMap->addComponent(m_transform);
	///////////////////////////////////////////////////////
}


