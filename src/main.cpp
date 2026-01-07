// Buatlah sebuah Game Engine mu sendiri untuk game FPS
// "Apapun bisa tercapai, asalkan kamu sabar" - Diandra

// TODO
// - Buatlah sebuah plane dan berjalan diatasnya tanpa fly mode (easy)
// - Buatlah library math mu sendiri (seperti matrix multiplacation, lookAt...) (medium)

// ! KawaiEngine adalah tempat dimana setiap apa yang saya pelajari mengenai Graphics Programming akan diterapkan di Engine ini

#define USE_DEBUG
#include "main.hpp"

int main(){
	// Setup Window System
	if(Window::setup()){
		Debug::debugme(MSG_ERROR, "Window::setup() is FAILED to Setup Window System");
		return RET_FAILURE;
	}
	else Debug::debugme(MSG_SUCCESS, "Window::setup() is SUCCESSFULLY to Setup Window System");
	
	// Setup Graphic System
	if(Graphic::setup()){
		Debug::debugme(MSG_ERROR, "Graphic::setup() is FAILED to Setup Graphic System");
		return RET_FAILURE;
	}
	else Debug::debugme(MSG_SUCCESS, "Graphic::setup() is SUCCESSFULLY to Setup Graphic System");

	// Setup Input System
	if(Input::setup()){
		Debug::debugme(MSG_ERROR, "Input::setup() is FAILED to Setup Input System");
		return RET_FAILURE;
	}
	else Debug::debugme(MSG_SUCCESS, "Input::setup() is SUCCESSFULLY to Setup Input System");

	// Main Looping
	Debug::debugme(MSG_INFO, "Window::looping() Enter the Main Looping");
	Window::looping();
	Debug::debugme(MSG_INFO, "Window::looping() Exit from the Main Looping");

	// Cleanup Graphic System
	Graphic::cleanup();
	Debug::debugme(MSG_SUCCESS, "Graphic::cleanup() is SUCCESSFULLY to cleanup");
	
	// Terminate Window System
	if(Window::terminate()){
		Debug::debugme(MSG_ERROR, "Window::terminate() is FAILED to Terminate Window System");
		return RET_FAILURE;
	}
	else Debug::debugme(MSG_SUCCESS, "Window::terminate() is SUCCESSFULLY to Terminate Window System");

	Debug::debugme(MSG_INFO, "Program Terminated");
	return RET_SUCCESS;
}
