#pragma once

#include <QMesh>
#include <QDiffuseSpecularMaterial>
#include <QTextureMaterial>

class ModelLoader
{
public:
	static Qt3DRender::QMesh* LoadMesh(QString file);
	static Qt3DExtras::QTextureMaterial* Texture(QString file);
	static Qt3DExtras::QDiffuseSpecularMaterial* Material(QColor diffuse);
};

