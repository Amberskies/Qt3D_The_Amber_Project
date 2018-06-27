#pragma once

#include <QComponent>

class FpsMonitor : public Qt3DCore::QComponent
{
	Q_OBJECT
		Q_PROPERTY(int RollingMeanFrameCount READ RollingMeanFrameCount
											 WRITE SetRollingMeanFrameCount
											 NOTIFY RollingMeanFrameCountChanged)
		Q_PROPERTY(float FramesPerSecond     READ FramesPerSecond
											 NOTIFY FramesPerSecondChanged)

public:
	explicit FpsMonitor(Qt3DCore::QNode *parent = nullptr);

	int RollingMeanFrameCount() const;
	float FramesPerSecond() const;

public slots:
	void SetRollingMeanFrameCount(int rollingMeanFrameCount);

signals:
	void RollingMeanFrameCountChanged(int rollingMeanFrameCount);
	void FramesPerSecondChanged(float framesPerSecond);

protected:
	void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change) override;

private:
	Qt3DCore::QNodeCreatedChangeBasePtr createNodeCreationChange() const override;

	float m_framesPerSecond;
	int m_rollingMeanFrameCount;
};

struct FpsMonitorData
{
	int rollingMeanFrameCount;
};
