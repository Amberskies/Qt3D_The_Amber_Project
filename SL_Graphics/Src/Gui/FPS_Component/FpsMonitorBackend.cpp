#include "FpsMonitorBackend.h"

#include "FpsMonitor.h"
#include "CustomAspect.h"

#include <QNodeCreatedChange>
#include <QPropertyUpdatedChange>

FpsMonitorBackend::FpsMonitorBackend()
	: Qt3DCore::QBackendNode(Qt3DCore::QBackendNode::ReadWrite)
{
	// Empty
}

void FpsMonitorBackend::AddFpsSample(float fpsSample)
{
	// Update the moving average.
	m_average.AddSample(fpsSample);

	// Calculate the average and notify the frontend.
	const auto meanFps = m_average.Average();
	auto e = Qt3DCore::QPropertyUpdatedChangePtr::create(peerId());
	e->setDeliveryFlags(Qt3DCore::QSceneChange::Nodes);
	e->setPropertyName("framesPerSecond");
	e->setValue(QVariant::fromValue(meanFps));
	notifyObservers(e);
}

void FpsMonitorBackend::sceneChangeEvent(const Qt3DCore::QSceneChangePtr & e)
{
	if (e->type() == Qt3DCore::PropertyUpdated)
	{
		const auto change = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(e);
		qDebug() << change->propertyName();

		if (change->propertyName() == QByteArrayLiteral("rollingMeanFrameCount"))
		{
			const auto newValue = change->value().toInt();
			
			if (newValue != m_rollingMeanFrameCount)
			{
				m_rollingMeanFrameCount = newValue;
				m_average = MovingAverage(newValue);
			}
			return;
		}
	}
	QBackendNode::sceneChangeEvent(e);
}

void FpsMonitorBackend::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr & change)
{
	const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<FpsMonitorData>>(change);
	const auto &data = typedChange->data;
	m_rollingMeanFrameCount = data.rollingMeanFrameCount;
	m_average = MovingAverage(m_rollingMeanFrameCount);
}

/////////////////////////////////////////////////////////////

FpsMonitorMapper::FpsMonitorMapper(CustomAspect * aspect)
	: m_aspect(aspect)
{
	Q_ASSERT(m_aspect);
}

Qt3DCore::QBackendNode * FpsMonitorMapper::create(const Qt3DCore::QNodeCreatedChangeBasePtr & change) const
{
	auto fpsMonitor = new FpsMonitorBackend;
	m_aspect->AddFpsMonitor(change->subjectId(), fpsMonitor);
	return fpsMonitor;
}

Qt3DCore::QBackendNode * FpsMonitorMapper::get(Qt3DCore::QNodeId id) const
{
	return m_aspect->fpsMonitor(id);
}

void FpsMonitorMapper::destroy(Qt3DCore::QNodeId id) const
{
	auto fpsMonitor = m_aspect->takeFpsMonitor(id);
	delete fpsMonitor;
}

