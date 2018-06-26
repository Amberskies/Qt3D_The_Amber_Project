#pragma once

#include <QCamera>
#include <Window3D.h>
#include <Camera3D.h>
//#include <Utils/Transform3D.h>

class Move3D
{
public:
	Move3D();
	~Move3D();

	void UpdateMove3D(class Window3D &win);

private:
	//Qt3DRender::QCamera *m_camera = nullptr;

	Camera3D m_camera;
	Transform3D m_transform;
};
