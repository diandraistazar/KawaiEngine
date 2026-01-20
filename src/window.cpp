#include "main.hpp"
#include "window.hpp"
#include "graphic.hpp"
#include "input.hpp"
#include "camera.hpp"
#include "display.hpp"
#include "debug.hpp"
#include <array>

GLFWwindow *Window::window = nullptr;
int Window::win_width = 960;
int Window::win_height = 660;

void setWindowHint(){
	std::array<int, 3*2> values = {
	//	Hint				 				Value
		GLFW_OPENGL_PROFILE, 		GLFW_OPENGL_CORE_PROFILE,
		GLFW_CONTEXT_VERSION_MAJOR, 4,
		GLFW_CONTEXT_VERSION_MINOR, 3,
	};

	for(int i = 0; i < values.size(); i+=2)
		glfwWindowHint(values[i], values[i+1]);
}

int Window::setup(){
	// Initialize GLFW
	if(!glfwInit()){
		Debug::debugme(M_ERROR, "Window::setup::glfwInit() returns false");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Window::setup::glfwInit() is SUCCESSFULLY to initialize");

	// Set window hints for next glfwCreateWindow call
	setWindowHint();
	Debug::debugme(M_SUCCESS, "Window::setup::setWindowHint() is SUCCESSFULLY to set hints for next glfwCreateWindow() call");

	// Create a window
	Window::window = glfwCreateWindow(Window::win_width, Window::win_height, PROGRAM "_" VERSION, nullptr, nullptr);
	if(!Window::window){
		Debug::debugme(M_ERROR, "Window::setup::glfwCreateWindow() returns null");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Window::setup::glfwCreateWindow() is SUCCESSFULLY to create a window");

	// Make the window pointer as the current context
	glfwMakeContextCurrent(Window::window);
	if(glfwGetCurrentContext() != Window::window){
		Debug::debugme(M_ERROR, "Window::setup::glfwGetCurrentContext() does not return the same window");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Window::setup::glfwMakeContextCurrent() is SUCCESSFULLY to make the window as the current context");

	// Load OpenGL 3.3 functions from Driver with Glad Loader
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		Debug::debugme(M_ERROR, "Window::setup::gladLoadGLLoader() returns false");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Window::setup::gladLoadGLLoader() is SUCCESSFULLY to load OpenGL 4.3 Functions");
	glfwSwapInterval(0);
	return RET_SUCCESS;
}

void Window::terminate(){
	glfwDestroyWindow(Window::window);
	glfwTerminate();
}

using namespace glm;
void Window::looping(){
	while(!glfwWindowShouldClose(Window::window)){		
		Input::zooming();
		Input::movement();
		Input::direction();
		glfwPollEvents();

		glm::mat4 matrix = Camera::projection() * Camera::view();
		Graphic::clear();
		Graphic::draw_light_cube(matrix);
		Graphic::draw_plane(matrix);
		glfwSwapBuffers(Window::window);

		Display::update_fps();
		Display::update_frametime();
		Debug::debugme(M_INFO, "FPS: %d, FRM: %f", Display::framerate, Display::frametime);
		Debug::debugme(M_INFO, "Position: %.2f %.2f %.2f, Direction: %.2f %.2f %.2f", Input::position.x, Input::position.y, Input::position.z, Input::looking.x, Input::looking.y, Input::looking.z);
		Debug::debugme(M_INFO, "Pitch: %.2f, Yaw: %.2f", Input::pitch, Input::yaw);
	}
}
