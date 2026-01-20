#pragma once

#include "glm_math.hpp"

struct Input{
	static float pitch, yaw;
	static float sensivity_pointer;
	static float movement_speed;
	static float zoom_speed;
	static glm::vec3 position, looking;

	static int setup();
	static void zooming();
	static void movement();
	static void direction();
};
