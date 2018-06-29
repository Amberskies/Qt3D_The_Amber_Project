#pragma once

#include <QEntity>

class TheSun : public Qt3DCore::QEntity
{
public:
	explicit TheSun(QEntity *root = nullptr);
	~TheSun();

	//Get
	Qt3DCore::QEntity * getTheSun();

	//Set

private:
	QEntity * m_rootEntity = nullptr;
	QEntity * m_theSun = nullptr;
};
