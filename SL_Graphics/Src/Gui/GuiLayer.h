#pragma once

#include <QEntity>
#include <QTransform>
#include <QExtrudedTextMesh>
#include <QDiffuseSpecularMaterial> 

#include <QString>
#include <QVector3D>

class GuiLayer : Qt3DCore::QEntity
{
public:
	explicit GuiLayer(Qt3DCore::QEntity *parent = nullptr);
	virtual ~GuiLayer();

	void setText(QString text, QVector3D position);

private:
	Qt3DExtras::QExtrudedTextMesh *m_textMesh = nullptr;
	Qt3DExtras::QDiffuseSpecularMaterial *m_textMaterial = nullptr;
	Qt3DCore::QTransform *m_textTransform = nullptr;
};