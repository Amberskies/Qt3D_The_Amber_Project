#pragma once

#include <QEntity>
#include "FPS_Component/FpsMonitor.h"

class FPS : public Qt3DCore::QEntity
{
public:
	FPS(QEntity *parent = nullptr);
	~FPS();

	float getFps();

private:
	FpsMonitor * m_fpsComponent = nullptr;
};