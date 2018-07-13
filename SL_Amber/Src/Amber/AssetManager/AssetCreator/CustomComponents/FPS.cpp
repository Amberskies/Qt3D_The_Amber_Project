#include "FPS.h"

FPS::FPS(QEntity * parent)
	: QEntity(parent)
{
	m_fpsComponent = new FpsMonitor(parent);
	m_fpsComponent->SetRollingMeanFrameCount(30);
	this->addComponent(m_fpsComponent);
}

FPS::~FPS()
{
	delete m_fpsComponent;
}

float FPS::getFps()
{
	return m_fpsComponent->FramesPerSecond();
}
