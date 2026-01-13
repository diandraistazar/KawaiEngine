#include "main.hpp"
#include "display.hpp"

int Display::framerate = 0;
float Display::frametime = 0.0f;

void Display::update_fps(){
	static float l_time = 0.0f;
	float time = glfwGetTime();
	static int frame = 0;

	if((time - l_time) < 1.0f){
		frame++;
		return;
	}

	Display::framerate = frame;
	l_time = time;
	frame = 0;
}

void Display::update_frametime(){
	static float l_time = 0;
	float time = glfwGetTime();
	Display::frametime = time - l_time;
	l_time = time;
}
