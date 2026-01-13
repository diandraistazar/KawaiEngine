#pragma once

#include "main.hpp"

class Display{
	public:
	static int framerate;
	static float frametime;

	public:
	static void update_fps();
	static void update_frametime();
};
