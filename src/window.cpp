#include "main.hpp"
#include <array>

GLFWwindow *window = nullptr;
int win_width = 900;
int win_height = 600;

void setWindowHint(){
	int values[3*2] = {
	//	Hint				 		Value
		GLFW_OPENGL_PROFILE, 		GLFW_OPENGL_CORE_PROFILE,
		GLFW_CONTEXT_VERSION_MAJOR, 4,
		GLFW_CONTEXT_VERSION_MINOR, 3,
		
	};
	for(int i = 0; i < sizeof(values) / sizeof(values[0]); i+=2)
		glfwWindowHint(values[i], values[i+1]);
}

int Window::setup(){
	// Initialize GLFW
	if(!glfwInit()){
		Debug::debugme(MSG_ERROR, "Window::setup::glfwInit() returns false");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Window::setup::glfwInit() is SUCCESSFULLY to initialize");

	// Set window hints for next glfwCreateWindow call
	setWindowHint();
	Debug::debugme(MSG_SUCCESS, "Window::setup::setWindowHint() is SUCCESSFULLY to set hints for next glfwCreateWindow() call");

	// Create a window
	window = glfwCreateWindow(win_width, win_height, PROGRAM "_" VERSION, nullptr, nullptr);
	if(!window){
		Debug::debugme(MSG_ERROR, "Window::setup::glfwCreateWindow() returns null");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Window::setup::glfwCreateWindow() is SUCCESSFULLY to create a window");

	// Make the window pointer as the current context
	glfwMakeContextCurrent(window);
	if(glfwGetCurrentContext() != window){
		Debug::debugme(MSG_ERROR, "Window::setup::glfwGetCurrentContext() does not return the same window");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Window::setup::glfwMakeContextCurrent() is SUCCESSFULLY to make the window as the current context");

	// Load OpenGL 3.3 functions from Driver with Glad Loader
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		Debug::debugme(MSG_ERROR, "Window::setup::gladLoadGLLoader() returns false");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Window::setup::gladLoadGLLoader() is SUCCESSFULLY to load OpenGL 3.3 Functions");
	return RET_SUCCESS;
}

int Window::terminate(){
	glfwTerminate();
	return RET_SUCCESS;
}

void Window::looping(){
	Graphic::VAO.bind(true);
	Graphic::program.use(true);
	
	while(!glfwWindowShouldClose(window)){
		Graphic::clear();
		Graphic::draw();		

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}
