#include "main.hpp"
#include "input.hpp"
#include "camera.hpp"
#include "window.hpp"

float Input::pitch = 0.0f, Input::yaw = 0.0f;
float Input::sensivity_pointer = 0.8f;
float Input::movement_speed = 1.0f;
float Input::zoom_speed = 50.0f;
glm::vec3 Input::position(0.0f, 0.0f, 0.0f), Input::looking(0.0f, 0.0f, -1.0f);

int Input::setup(){
	glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return RET_SUCCESS;
}

void Input::zooming(){
	static float last_time = 0.0f;
	float time = glfwGetTime(), delta = time - last_time;

	if(glfwGetMouseButton(Window::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		Camera::fov -= zoom_speed * delta;
	}
	else if(glfwGetMouseButton(Window::window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
		Camera::fov += zoom_speed * delta;
	}

	if(Camera::fov < 0.1f)
		Camera::fov = 0.1f;

	last_time = time;
}

void Input::movement(){
	static float last_time = 0;
	float time = glfwGetTime();
	float delta = time - last_time;
	
	if(glfwGetKey(Window::window, GLFW_KEY_W) == GLFW_PRESS){
		position += looking * movement_speed * delta;
	}
	if(glfwGetKey(Window::window, GLFW_KEY_S) == GLFW_PRESS){
		position -= looking * movement_speed * delta;
	}
	if(glfwGetKey(Window::window, GLFW_KEY_A) == GLFW_PRESS){
		position -= glm::cross(looking, glm::vec3(0.0f, 1.0f, 0.0f)) * movement_speed * delta;
	}
	if(glfwGetKey(Window::window, GLFW_KEY_D) == GLFW_PRESS){
		position += glm::cross(looking, glm::vec3(0.0f, 1.0f, 0.0f)) * movement_speed * delta;
	}

	if(position.y > 0.0f || position.y < 0.0f)
		position.y = 0.0f;

	last_time = time;
}

void Input::direction(){
	static double last_xpos = 0.0f, last_ypos = 0.0f;
	double xpos = 0.0f, ypos = 0.0f;

	glfwGetCursorPos(Window::window, &xpos, &ypos);
	if(last_xpos != 0.0f && last_ypos != 0.0f){
		yaw += (xpos - last_xpos) * sensivity_pointer / Window::win_height * 180.0f;
		pitch += (ypos - last_ypos) * sensivity_pointer / Window::win_width * 180.0f;
	
		if(pitch > 89.9f)
			pitch = 89.9f;
		else if(pitch < -89.9f)
			pitch =  -89.9f;

		if(yaw > 360.0f)
			yaw = -360.0f;
		else if(yaw < -360.0f)
			yaw = 360.0f;

		float yaw_radians = glm::radians(yaw);
		float pitch_radians = glm::radians(pitch);
		looking.x = cos(yaw_radians) * cos(pitch_radians);
		looking.y = sin(pitch_radians) * -1.0f;
		looking.z = sin(yaw_radians) * cos(pitch_radians);
	}
	last_xpos = xpos;
	last_ypos = ypos;
}
