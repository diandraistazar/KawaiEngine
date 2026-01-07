#define USE_DEBUG
#include "main.hpp"

float Input::pitch = 0.0f, Input::yaw = 0.0f;
float Input::sensivity_pointer = 1.0f;
float Input::movement_speed = 1.0f;
glm::vec3 Input::position(0.0f, 0.0f, 0.0f), Input::direction(0.0f, 0.0f, -1.0f);

int Input::setup(){
	glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return RET_SUCCESS;
}

void Input::get_movement(){
	static float l_time = 0;
	float time = glfwGetTime();
	float delta = time - l_time;
	
	if(glfwGetKey(Window::window, GLFW_KEY_W) == GLFW_PRESS){
		position += direction * movement_speed * delta;
	}
	if(glfwGetKey(Window::window, GLFW_KEY_S) == GLFW_PRESS){
		position -= direction * movement_speed * delta;
	}
	if(glfwGetKey(Window::window, GLFW_KEY_A) == GLFW_PRESS){
		position -= glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)) * movement_speed * delta;
	}
	if(glfwGetKey(Window::window, GLFW_KEY_D) == GLFW_PRESS){
		position += glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)) * movement_speed * delta;
	}

	if(position.y > 0.0f || position.y < 0.0f)
		position.y = 0.0f;

	l_time = time;
}

void Input::get_direction(){
	static double l_xpos = 0.0f, l_ypos = 0.0f;
	double xpos = 0.0f, ypos = 0.0f;

	glfwGetCursorPos(Window::window, &xpos, &ypos);
	if(l_xpos != 0.0f && l_ypos != 0.0f){
		yaw += (xpos - l_xpos) * sensivity_pointer / Window::win_height * 180.0f;
		pitch += (ypos - l_ypos) * sensivity_pointer / Window::win_width * 180.0f;
	
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
		direction.x = cos(yaw_radians) * cos(pitch_radians);
		direction.y = sin(pitch_radians) * -1.0f;
		direction.z = sin(yaw_radians) * cos(pitch_radians);
	}
	l_xpos = xpos;
	l_ypos = ypos;
}
