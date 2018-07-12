#pragma once

#include <QAspectJob>
#include <QSharedPointer>

class CustomAspect;

class UpdateFpsMonitorsJob : public Qt3DCore::QAspectJob
{
public:
	explicit UpdateFpsMonitorsJob(CustomAspect *aspect);

	void SetFrameTimeDelta(qint64 dt);
	void run() override;

private:
	CustomAspect * m_aspect;
		qint64 m_dt;
};

using UpdateFpsMonitorsJobPtr = QSharedPointer<UpdateFpsMonitorsJob>;
