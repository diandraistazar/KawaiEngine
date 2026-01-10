#pragma once

#include "main.hpp"

class Window{
	public:
	static GLFWwindow *window;
	static int win_width;
	static int win_height;

	public:
	static int setup();
	static void terminate();
	static void looping();
};
