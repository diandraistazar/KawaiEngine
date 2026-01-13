#pragma once

#include "main.hpp"
#include "glm_math.hpp"

class Camera{
	public:
	static float fov;
	static float aspect_ratio;
	static float near_plane;
	static float far_plane;

	public:
	static glm::mat4 view();
	static glm::mat4 projection();
};
