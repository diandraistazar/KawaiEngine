#pragma once

#include "main.hpp"

class Display{
	public:
	static int framerate;
	static float frametime;

	public:
	static void get_fps();
	static void get_frametime();
};
