#include "ModelLoader.h"
#include <QTexture>


Qt3DRender::QMesh * ModelLoader::LoadMesh(QString file)
{
	Qt3DRender::QMesh *newMesh = new Qt3DRender::QMesh();
	newMesh->setSource(QUrl::fromLocalFile(file));
	return newMesh;
}

Qt3DExtras::QTextureMaterial * ModelLoader::Texture(QString file)
{
	Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D();
	Qt3DRender::QTextureImage *tex = new Qt3DRender::QTextureImage();
	tex->setSource(QUrl::fromLocalFile(file));
	texture->addTextureImage(tex);
	Qt3DExtras::QTextureMaterial *textureMaterial = new Qt3DExtras::QTextureMaterial();
	textureMaterial->setTexture(texture);
	return textureMaterial;
}

Qt3DExtras::QPhongMaterial * ModelLoader::Material(QColor diffuse)
{
	Qt3DExtras::QPhongMaterial *newMaterial = new Qt3DExtras::QPhongMaterial();
	newMaterial->setDiffuse(diffuse);
	return newMaterial;
}
