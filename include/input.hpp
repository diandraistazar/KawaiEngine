#pragma once

#include "main.hpp"
#include "glm_math.hpp"

struct Input{
	static float pitch, yaw;
	static float sensivity_pointer;
	static float movement_speed;
	static float zoom_speed;
	static glm::vec3 position, direction;

	static int setup();
	static void get_zooming();
	static void get_movement();
	static void get_direction();
};
