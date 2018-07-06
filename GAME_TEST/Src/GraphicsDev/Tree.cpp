#include "Tree.h"
#include <QTransform>
#include <QTexture>
#include <Utils/ModelLoader.h>

Tree::Tree(QEntity * root)
	: QEntity(root)
{
	m_TreeMesh = ModelLoader::LoadMesh("../Assets/Maps/BaseTree.obj");
	m_TreeMaterial = new Qt3DExtras::QDiffuseSpecularMaterial;
	Qt3DRender::QTexture2D *texture = new Qt3DRender::QTexture2D();
	Qt3DRender::QTextureImage *tex = new Qt3DRender::QTextureImage();
	tex->setSource(QUrl::fromLocalFile("../Assets/Maps/BaseTree.png"));

	texture->addTextureImage(tex);
	Qt3DRender::QTextureWrapMode twm(Qt3DRender::QTextureWrapMode::Repeat);
	texture->setWrapMode(twm);
	texture->setGenerateMipMaps(true);
	texture->setSamples(4);

	m_TreeMaterial->setAmbient({ 30, 25, 20, 255 });
	//m_TreeMaterial->setDiffuse(QVariant::fromValue(texture));
	m_TreeMaterial->setSpecular(0.01f);
	m_TreeMaterial->setShininess(0.1f);
}

Tree::~Tree()
{
//	delete [] m_Tree;
}

void Tree::createTree(int index, QVector3D location)
{
	m_Tree[index] = new Qt3DCore::QEntity(this);
	Qt3DCore::QTransform *TreeTransform = new Qt3DCore::QTransform();
	TreeTransform->setTranslation(location);

	m_Tree[index]->addComponent(m_TreeMesh);
	m_Tree[index]->addComponent(m_TreeMaterial);
	m_Tree[index]->addComponent(TreeTransform);

}

Qt3DCore::QEntity * Tree::getTree()
{
	return this;
}
