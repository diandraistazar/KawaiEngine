#pragma once

#include "main.hpp"

class Input{
	public:
	static float pitch, yaw;
	static float sensivity_pointer;
	static float movement_speed;
	static glm::vec3 position, direction;

	public:
	static int setup();
	static void mouse_mode();
	static void get_movement();
	static void get_direction();
};
