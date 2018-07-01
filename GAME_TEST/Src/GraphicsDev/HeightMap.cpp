#include "HeightMap.h"

HeightMap::HeightMap(QEntity * parent)
	: QEntity(parent)
	, m_heightMap(new QEntity(parent))
	, m_root(new QEntity(parent))
{
	//m_mesh = new QPlaneMesh();
	//m_mesh->setWidth(20.0f);
	//m_mesh->setHeight(20.0f);
	//m_mesh->setMeshResolution({ 4, 4 });

	//m_material = new Qt3DExtras::QDiffuseSpecularMaterial();
	//m_material->setAmbient(QColor(Qt::darkGreen));

}

void HeightMap::createHeightMap()
{
	qWarning("HeightMap under construction.");
	//calcHeight();

	//m_transform = new Qt3DCore::QTransform();
	//m_transform->setTranslation(QVector3D(10.0f, 0.0f, 10.0f));


	//m_heightMap->addComponent(m_mesh);
	//m_heightMap->addComponent(m_material);
	//m_heightMap->addComponent(m_transform);
	DrawLine();
}
void HeightMap::calcHeight()
{
	QVector3D height = { 0.0f, 0.5f, 0.0f };

	int firstVertex = m_mesh->firstVertex();
	int vertexCount = m_mesh->vertexCount();
	m_currentMap = m_mesh->geometry();

	qDebug() << "firstVertex : " << firstVertex;
	qDebug() << "vertexCount : " << vertexCount;
	qDebug() << "Geometry    : " << m_currentMap;
}
#include <QGeometry>
#include <QBuffer>
#include <QAttribute>
//#include <QtGlobal>
#include <QMesh>

void HeightMap::DrawLine()
{
	float vertex_array[3 * 2]; // xyz*2 for two vertices

	int ix = 0;
	vertex_array[ix++] = 0.0f;
	vertex_array[ix++] = 0.0f;
	vertex_array[ix++] = 0.0f;

	vertex_array[ix++] = 1.0f; // X-axis.
	vertex_array[ix++] = 0.0f;
	vertex_array[ix++] = 0.0f;

	uint index_array[2]; // used to connect vertex 0 and 1 to make a line.

	ix = 0;
	index_array[ix++] = 0;
	index_array[ix++] = 1;

	qWarning("Lets Draw a Red line From 0,0,0 to X+1");
	//////////////////////////////////////////////////////

	Qt3DRender::QGeometry *geometry = new Qt3DRender::QGeometry;

	//////////////////////////////////////////////////////
	// initialize vertex attribute (positions only)
	QByteArray bufferBytes;
	const int num_vertices = 2;
	const quint32 elementSize = 3; // float xyz
	const quint32 stride = elementSize * sizeof(float);
	bufferBytes.resize(stride *num_vertices);

	memcpy(bufferBytes.data(), reinterpret_cast<const char*>(vertex_array), bufferBytes.size());

	Qt3DRender::QBuffer *buf(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer));
	buf->setData(bufferBytes);

	qWarning("Verticies Set into a buffer");
	/////////////////////////////////////////////////////
	Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute(buf,
		Qt3DRender::QAttribute::defaultPositionAttributeName(),
		Qt3DRender::QAttribute::Float,
		3,
		num_vertices,
		0,
		stride,
		0);

	geometry->addAttribute(positionAttribute);

	qWarning("Verticies added to geometry");
	//////////////////////////////////////////////////
	//initialize connectivity - connect the dots///////

	Q_ASSERT(sizeof(int) == sizeof(quint32));


	int num_indices = 2;
	QByteArray indexBytes;
	indexBytes.resize(num_indices * sizeof(quint32));

	memcpy(indexBytes.data(), reinterpret_cast<const char*>(index_array), indexBytes.size());

	Qt3DRender::QBuffer *indexBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer));
	indexBuffer->setData(indexBytes);
	qWarning("Index buffer setup");
	////////////////////////////////////////////////////
	Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute(indexBuffer,
		Qt3DRender::QAttribute::UnsignedInt,
		1,
		num_indices);
	indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
	geometry->addAttribute(indexAttribute);

	qWarning("Index added to geometry");
	////////////////////////////////////////////////////////

	Qt3DRender::QMesh *x_axis_line = new Qt3DRender::QMesh();

	x_axis_line->setGeometry(geometry);
	x_axis_line->geometryChanged(geometry);
	x_axis_line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
	qWarning("x_axis_line now holds all our data.");

	m_material = new Qt3DExtras::QDiffuseSpecularMaterial();
	m_material->setAmbient(QColor(Qt::red));

	m_transform = new Qt3DCore::QTransform();
	m_transform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));


	QEntity *x_axis_entity = new QEntity(m_root);
	x_axis_entity->addComponent(x_axis_line);
	x_axis_entity->addComponent(m_material);
	x_axis_entity->addComponent(m_transform);
	///////////////////////////////////////////////////////
}


