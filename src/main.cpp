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
	int (*p_function)(void);
	void (*p_cleanup)(void);
};
Setup init[] = {
	{ "Window::setup()", Window::setup, Window::terminate },
	{ "Graphic::setup()", Graphic::setup, Graphic::cleanup },
	{ "Input::setup()", Input::setup, nullptr },
};

struct Engine{
	static int setup(){
		for(int index = 0; index < sizeof(init)/sizeof(init[0]); index++){
			if(init[index].p_function){
				int ret = init[index].p_function();
				if(ret){
					Debug::debugme(M_ERROR, "%s is FAILED", init[index].s_name);
					return RET_FAILURE;
				}
				Debug::debugme(M_SUCCESS, "%s is SUCCESSFULLY", init[index].s_name);
			}
		}
		return RET_SUCCESS;
	}
	static void cleanup(){
		for(int index = 0; index < sizeof(init)/sizeof(init[0]); index++){
			if(init[index].p_cleanup)
				init[index].p_cleanup();
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
	return RET_SUCCESS;
}
