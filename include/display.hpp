#pragma once

struct Display{
	static int framerate;
	static float frametime;

	static void update_fps();
	static void update_frametime();
};
