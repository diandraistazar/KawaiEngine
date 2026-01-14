#pragma once

#include "main.hpp"
#include "glm_math.hpp"

struct Camera{
	static float fov;
	static float aspect_ratio;
	static float near_plane;
	static float far_plane;

	static glm::mat4 view();
	static glm::mat4 projection();
};
