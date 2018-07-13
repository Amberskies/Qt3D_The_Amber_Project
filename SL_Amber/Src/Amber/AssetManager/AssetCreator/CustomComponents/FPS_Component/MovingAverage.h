#pragma once

#include <QVector>

class MovingAverage
{
public:
	explicit MovingAverage(uint samples = 3);

	void AddSample(float sample);
	float Average() const;

private:
	uint m_maxSampleCount;
	uint m_sampleCount;
	uint m_currentSample;
	float m_total;
	QVector<float> m_samples;
};