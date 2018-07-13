#pragma once

#include <QAbstractAspect>
#include <QObject>
#include "UpdateFpsMonitorsJob.h"

class FpsMonitorBackend;

class CustomAspect : public Qt3DCore::QAbstractAspect
{

	Q_OBJECT

public:
	CustomAspect(QObject *parent = nullptr);

	void AddFpsMonitor(Qt3DCore::QNodeId id, FpsMonitorBackend *fpsMonitor);
	FpsMonitorBackend *fpsMonitor(Qt3DCore::QNodeId id);
	FpsMonitorBackend *takeFpsMonitor(Qt3DCore::QNodeId id);

	const QHash<Qt3DCore::QNodeId, FpsMonitorBackend*> &fpsMonitors() const
	{
		return m_fpsMonitors;
	}

protected:
	QVector<Qt3DCore::QAspectJobPtr> jobsToExecute(qint64 time) override;

private:
	QHash<Qt3DCore::QNodeId, FpsMonitorBackend*> m_fpsMonitors;
	UpdateFpsMonitorsJobPtr m_updateMonitorsJob;
	qint64 m_lastTime;
};