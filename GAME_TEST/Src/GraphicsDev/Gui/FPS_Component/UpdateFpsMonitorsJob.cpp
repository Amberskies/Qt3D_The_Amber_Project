#include "UpdateFpsMonitorsJob.h"

#include "CustomAspect.h"
#include "FpsMonitorBackend.h"

UpdateFpsMonitorsJob::UpdateFpsMonitorsJob(CustomAspect * aspect)
	: Qt3DCore::QAspectJob()
	, m_aspect(aspect)
{
	Q_ASSERT(aspect);
}

void UpdateFpsMonitorsJob::SetFrameTimeDelta(qint64 dt)
{
	m_dt = dt;
}

void UpdateFpsMonitorsJob::run()
{
	// Iterate over all the enabled fps monitors and add
	// the instantaneous fps value to thier moving averages.
	const float fps = 1.0f / (float(m_dt) * 1.0e-9);
	const auto &fpsMonitors = m_aspect->fpsMonitors();

	for (const auto fpsMonitor : fpsMonitors)
	{
		// dont process disabled monitors
		if (!fpsMonitor->isEnabled()) continue;
		fpsMonitor->AddFpsSample(fps);
	}
}
