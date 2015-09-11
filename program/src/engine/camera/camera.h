#ifndef ENGINE_CAMERA_CAMERA_H
#define ENGINE_CAMERA_CAMERA_H

#include "../engine_pch.h"
#include "../math/math.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void Update();
	const Matrix& GetViewMat();

private:
	Vector position_;
	Vector rotation_;
	Matrix viewMat_;
};

#endif