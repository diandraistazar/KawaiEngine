// Buatlah sebuah Game Engine mu sendiri untuk game FPS
// "Apapun bisa tercapai, asalkan kamu sabar" - Diandra

// TODO
// - Buatlah sebuah plane dan berjalan diatasnya tanpa fly mode (easy)
// - Buatlah library math mu sendiri (seperti matrix multiplacation, lookAt...) (medium)

// ! KawaiEngine adalah tempat dimana setiap apa yang saya pelajari mengenai Graphics Programming akan diterapkan di Engine ini

#include "main.hpp"
#include "window.hpp"
#include "graphic.hpp"
#include "input.hpp"
#include "debug.hpp"

struct Setup{
	const char *s_name;
	int (*p_setup)(void);
	void (*p_terminate)(void);
} init[] = {
//		Strings					Setup Functions	Terminate Functions
	{ "Window::setup()", 	Window::setup, 	Window::terminate },
	{ "Graphic::setup()", 	Graphic::setup, 	Graphic::terminate },
	{ "Input::setup()", 		Input::setup, 		nullptr },
};

struct Engine{
	static int setup(){
		for(Setup &function : init){
			if(!function.p_setup)
				return RET_FAILURE;
			
			int r_value = function.p_setup();
			if(r_value){
				Debug::debugme(M_ERROR, "%s is FAILED to setup", function.s_name);
				return RET_FAILURE;
			}
			Debug::debugme(M_SUCCESS, "%s is SUCCESSFULLY to setup", function.s_name);
		}
		return RET_SUCCESS;
	}
	static void cleanup(){
		for(Setup &function : init){
			if(!function.p_terminate){
				Debug::debugme(M_WARNING, "%s is have not a terminate function #SKIP", function.s_name);
				continue;
			}
			function.p_terminate();
			Debug::debugme(M_SUCCESS, "%s is SUCCESSFULLY to terminate", function.s_name);
		}
	}
	static void run(){
		Debug::debugme(M_INFO, "Enter Window::looping()");
		Window::looping();
		Debug::debugme(M_INFO, "Exit Window::looping()");
	}
};

int main(){
	if(Engine::setup())
		return RET_FAILURE;
	
	Engine::run();
	Engine::cleanup();
	
	Debug::debugme(M_SUCCESS, "Program Terminated");
	return RET_SUCCESS;
}
