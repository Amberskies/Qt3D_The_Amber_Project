#pragma once

#include <QBackendNode>
#include "MovingAverage.h"

class FpsMonitorBackend : public Qt3DCore::QBackendNode
{
public:
	FpsMonitorBackend();

	void AddFpsSample(float fpsSample);

protected:
	void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e) override;

private:
	void initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change) override;

	int m_rollingMeanFrameCount;
	MovingAverage m_average;
};

class CustomAspect;

class FpsMonitorMapper : public Qt3DCore::QBackendNodeMapper
{
public:
	explicit FpsMonitorMapper(CustomAspect *aspect);

	Qt3DCore::QBackendNode* create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const override;
	Qt3DCore::QBackendNode* get(Qt3DCore::QNodeId id) const override;
	void destroy(Qt3DCore::QNodeId id) const override;

private:
	CustomAspect * m_aspect;
};
