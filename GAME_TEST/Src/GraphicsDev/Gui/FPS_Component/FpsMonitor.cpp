#include "FpsMonitor.h"

#include <QPropertyUpdatedChange>

FpsMonitor::FpsMonitor(Qt3DCore::QNode *parent)
	: Qt3DCore::QComponent(parent)
	, m_rollingMeanFrameCount(5)
	, m_framesPerSecond(0.0f)
{
	// Empty
}

int FpsMonitor::RollingMeanFrameCount() const
{
	return m_rollingMeanFrameCount;
}

float FpsMonitor::FramesPerSecond() const
{
	return  m_framesPerSecond;
}

void FpsMonitor::SetRollingMeanFrameCount(int rollingMeanFrameCount)
{
	if (m_rollingMeanFrameCount == rollingMeanFrameCount) return;
	m_rollingMeanFrameCount = rollingMeanFrameCount;
	emit RollingMeanFrameCountChanged(m_rollingMeanFrameCount);
}

void FpsMonitor::sceneChangeEvent(const Qt3DCore::QSceneChangePtr & change)
{
	if (change->type() == Qt3DCore::PropertyUpdated)
	{
		const auto e = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(change);

		if (e->propertyName() == QByteArrayLiteral("framesPerSecond"))
		{
			const auto fps = e->value().toFloat();

			if (!qFuzzyCompare(fps, m_framesPerSecond))
			{
				m_framesPerSecond = fps;
				const auto wasBlocked = blockNotifications(true);
				emit FramesPerSecondChanged(fps);
				blockNotifications(wasBlocked);
			}
			return;
		}
	}
	QComponent::sceneChangeEvent(change);
}

Qt3DCore::QNodeCreatedChangeBasePtr FpsMonitor::createNodeCreationChange() const
{
	auto creationChange = Qt3DCore::QNodeCreatedChangePtr<FpsMonitorData>::create(this);
	auto &data = creationChange->data;
	data.rollingMeanFrameCount = m_rollingMeanFrameCount;
	return creationChange;
}
