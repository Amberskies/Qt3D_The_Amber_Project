#include "Tree.h"
#include <QTransform>
#include <Utils/ModelLoader.h>

Tree::Tree(QEntity * root)
	: QEntity(root)
{
	m_TreeMesh = ModelLoader::LoadMesh("../Assets/Maps/BaseTree.obj");
	m_TreeMaterial = ModelLoader::Texture("../Assets/Maps/BaseTree.png");
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
