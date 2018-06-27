#pragma once

#include <QCamera>
#include <Window3D.h>

class Move3D
{
public:
	Move3D();
	~Move3D();

	void UpdateMove3D(class Window3D &win);

private:
	Qt3DRender::QCamera * m_cam = nullptr;
};
