#pragma once

#include <QEntity>
#include <QMesh>
#include <QDiffuseSpecularMaterial>
#include <QTextureMaterial>
#include <QVector3D>

class Tree : public Qt3DCore::QEntity
{
public:
	explicit Tree(QEntity *root = nullptr);
	~Tree();

	void createTree(int index, QVector3D location);
	//Get
	Qt3DCore::QEntity * getTree();

	//Set

private:
	QEntity * m_rootEntity = nullptr;
	QEntity * m_Tree[100];
	Qt3DRender::QMesh *m_TreeMesh = nullptr;
	Qt3DExtras::QTextureMaterial *m_TreeMaterial = nullptr;

};