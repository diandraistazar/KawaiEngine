#pragma once

#include "main.hpp"

struct Window{
	static GLFWwindow *window;
	static int win_width;
	static int win_height;

	static int setup();
	static void terminate();
	static void looping();
};
