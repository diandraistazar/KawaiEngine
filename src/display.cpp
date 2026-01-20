#include "main.hpp"
#include "display.hpp"

int Display::framerate = 0;
float Display::frametime = 0.0f;

void Display::update_fps(){
	static float last_time = 0.0f;
	float time = glfwGetTime();
	static int frame = 0;

	if((time - last_time) < 1.0f){
		frame++;
		return;
	}

	framerate = frame;
	last_time = time;
	frame = 0;
}

void Display::update_frametime(){
	static float last_time = 0;
	float time = glfwGetTime();
	
	frametime = time - last_time;
	last_time = time;
}
