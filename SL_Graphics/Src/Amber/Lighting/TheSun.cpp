#include "TheSun.h"

#include <QPointLight>
#include <QTransform>

TheSun::TheSun(QEntity * root)
	: m_rootEntity(root)
	, m_theSun(new QEntity(m_rootEntity))
{
	Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight();
	light->setColor(QColor(QColor(QRgb(0xD100908))));
	light->setIntensity(0.8f);
	m_theSun->addComponent(light);

	Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform();
	lightTransform->setTranslation(QVector3D(0.0f, 50.0f, 1.0f));
	m_theSun->addComponent(lightTransform);

	qWarning("The Sun Has come out - it's sooo Nice!");
}

TheSun::~TheSun()
{
	qWarning("Oops the Sun was Destroyed!");
	delete m_theSun;
}

Qt3DCore::QEntity * TheSun::getTheSun()
{
	return m_theSun;
}
