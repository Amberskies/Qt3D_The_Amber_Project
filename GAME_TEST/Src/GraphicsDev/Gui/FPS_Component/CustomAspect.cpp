#include "CustomAspect.h"

#include "FpsMonitor.h"
#include "FpsMonitorBackend.h"
#include "UpdateFpsMonitorsJob.h"

CustomAspect::CustomAspect(QObject *parent) :
	  Qt3DCore::QAbstractAspect(parent)
	, m_updateMonitorsJob(new UpdateFpsMonitorsJob(this))
{
	// Register the mapper to handle creation, lookup, and destruction of backend nodes.
	auto mapper = QSharedPointer<FpsMonitorMapper>::create(this);
	registerBackendType<FpsMonitor>(mapper);
}

void CustomAspect::AddFpsMonitor(Qt3DCore::QNodeId id, FpsMonitorBackend * fpsMonitor)
{
	m_fpsMonitors.insert(id, fpsMonitor);
}

FpsMonitorBackend * CustomAspect::fpsMonitor(Qt3DCore::QNodeId id)
{
	return m_fpsMonitors.value(id, nullptr);
}

FpsMonitorBackend * CustomAspect::takeFpsMonitor(Qt3DCore::QNodeId id)
{
	return m_fpsMonitors.take(id);
}

QVector<Qt3DCore::QAspectJobPtr> CustomAspect::jobsToExecute(qint64 time)
{
	const auto dt = time - m_lastTime;
	m_lastTime = time;
	m_updateMonitorsJob->SetFrameTimeDelta(dt);
	return { m_updateMonitorsJob };
}
