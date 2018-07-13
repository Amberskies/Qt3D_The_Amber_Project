#include "GuiLayer.h"
#include "../../AssetManager/LoadData/ModelLoader.h"



GuiLayer::GuiLayer(QEntity * parent)
	: QEntity(parent)
{

	m_textMesh = new Qt3DExtras::QExtrudedTextMesh();
	m_textMesh->setDepth(0.4f);
	//m_textMesh->setFont(const QFont &font);
	m_textMesh->setText(" .... ");

	m_textMaterial = ModelLoader::Material(QColor(QRgb(0xEEAA10)));

	m_textTransform = new Qt3DCore::QTransform();
	m_textTransform->setTranslation(QVector3D(0.0f, -10.0f, 0.0f));
	//m_textTransform->setRotationY(-135.0f);
	//m_textTransform->setRotationX(-25.0f);

	this->addComponent(m_textMesh);
	this->addComponent(m_textMaterial);
	this->addComponent(m_textTransform);
}

GuiLayer::~GuiLayer()
{
	delete m_textTransform;
	delete m_textMaterial;
	delete m_textMesh;
}


void GuiLayer::setText(QString text, QVector3D position)
{
	//QVector3D pos;
	//pos.setX(position.x() + 5.0f);
	//pos.setY(position.y() + 5.0f);
	//pos.setZ(position.z());

	m_textMesh->setText(text);
	m_textTransform->setTranslation(position);
}
