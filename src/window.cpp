#define USE_DEBUG
#include "main.hpp"
#include <array>


GLFWwindow *Window::window = nullptr;
int Window::win_width = 960;
int Window::win_height = 660;

void setWindowHint(){
	std::array<int, 3*2> values = {
	//	Hint				 		Value
		GLFW_OPENGL_PROFILE, 		GLFW_OPENGL_CORE_PROFILE,
		GLFW_CONTEXT_VERSION_MAJOR, 4,
		GLFW_CONTEXT_VERSION_MINOR, 3,
		
	};
	for(int i = 0; i < (int)values.size(); i+=2)
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
	Window::window = glfwCreateWindow(Window::win_width, Window::win_height, PROGRAM "_" VERSION, nullptr, nullptr);
	if(!Window::window){
		Debug::debugme(MSG_ERROR, "Window::setup::glfwCreateWindow() returns null");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Window::setup::glfwCreateWindow() is SUCCESSFULLY to create a window");

	// Make the window pointer as the current context
	glfwMakeContextCurrent(Window::window);
	if(glfwGetCurrentContext() != Window::window){
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
	glfwDestroyWindow(Window::window);
	glfwTerminate();
	return RET_SUCCESS;
}

void Window::looping(){
	Graphic::program.use(true);

		
	while(!glfwWindowShouldClose(Window::window)){
		Display::get_fps();
		Display::get_frametime();
		
		Graphic::VAO[V_PLANE].resetMatrix(1.0f);
		Graphic::VAO[V_PLANE].translate(0.0f, -0.5f, 0.0f);
		Graphic::VAO[V_PLANE].rotate(90.0f, 1.0f, 0.0f, 0.0f);
		Graphic::VAO[V_PLANE].scale(2.0f, 2.0f, 2.0f);

		Graphic::VAO[V_BOX].resetMatrix(1.0f);
		Graphic::VAO[V_BOX].translate(0.0f, 0.3f, 0.0f);
		Graphic::VAO[V_BOX].rotate(glfwGetTime() * 180.0f / 3.14f, 0.0f, 1.0f, 0.0f);

		Graphic::clear();
		for(int i = 0; i < V_TOTAL; i++){
			glm::mat4 matrix = Camera::projection() * Camera::view() * Graphic::VAO[i].getMatrix();
			Graphic::VAO[i].bind(true);
			Graphic::transform(matrix);
			Graphic::draw(Graphic::VAO[i]);		
		}
		glfwPollEvents();
		glfwSwapBuffers(Window::window);
		Debug::debugme(MSG_INFO, "FPS: %d, FRM: %f", Display::framerate, Display::frametime);
	}
}
