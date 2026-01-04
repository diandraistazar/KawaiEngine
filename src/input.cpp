#define USE_DEBUG
#include "main.hpp"

float Input::sensivity_pointer = 0.5f;
float Input::movement_speed = 1.0f;

int Input::setup(){
	glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return RET_SUCCESS;
}

void Input::get_movement(glm::vec3 &vector, glm::vec3 &direction){
	static float l_time = 0;
	float time = glfwGetTime();
	float delta = time - l_time;
	
	if(glfwGetKey(Window::window, GLFW_KEY_W) == GLFW_PRESS){
		vector += direction * movement_speed * delta;
	}
	if(glfwGetKey(Window::window, GLFW_KEY_S) == GLFW_PRESS){
		vector -= direction * movement_speed * delta;
	}
	if(glfwGetKey(Window::window, GLFW_KEY_A) == GLFW_PRESS){
		vector -= glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)) * movement_speed * delta;
	}
	if(glfwGetKey(Window::window, GLFW_KEY_D) == GLFW_PRESS){
		vector += glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)) * movement_speed * delta;
	}

	if(vector.y > 0.0f || vector.y < 0.0f)
		vector.y = 0.0f;

	l_time = time;
}

void Input::get_direction(glm::vec3 &vector){
	static float pitch = 0.0f, yaw = 0.0f;
	double xpos = 0.0f, ypos = 0.0f;

	glfwGetCursorPos(Window::window, &xpos, &ypos);
	float y = ypos * sensivity_pointer;
	float x = xpos * sensivity_pointer;
	pitch = y / Window::win_height * 360.0f;
	yaw = x / Window::win_width * 360.0f;
	
	if(pitch > 89.9f)
		pitch = 89.9f;
	else if(pitch < -89.9f)
		pitch =  -89.9f;

	Debug::debugme(MSG_INFO, "pitch: %.1f, yaw: %.1f", pitch, yaw);

	float yaw_radians = glm::radians(yaw);
	float pitch_radians = glm::radians(pitch);
	vector.x = cos(yaw_radians) * cos(pitch_radians);
	vector.y = sin(pitch_radians) * -1.0f;
	vector.z = sin(yaw_radians) * cos(pitch_radians);
}
