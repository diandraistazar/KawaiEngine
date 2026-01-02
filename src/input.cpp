#include "main.hpp"

float Input::sensivity_pointer = 0.5f;
float Input::movement_speed = 1.0f;

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
	static double last_x_pos = 0.0f, last_y_pos = 0.0f;
	static float l_time = 0.0f;
	static float pitch = 0.0f, yaw = 0.0f;
	double x_pos, y_pos;
	float time = glfwGetTime();
	float delta = time - l_time;

	glfwGetCursorPos(Window::window, &x_pos, &y_pos);
	if(last_x_pos == 0.0f && last_y_pos == 0.0f){
		last_x_pos = x_pos;
		last_y_pos = y_pos;
	}
	pitch += (y_pos - last_y_pos) * 360.0f * sensivity_pointer * delta;
	yaw += (x_pos - last_x_pos) * 360.0f * sensivity_pointer * delta;

	if(pitch > 89.9f)
		pitch = 89.9f;
	else if(pitch < -89.9f)
		pitch =  -89.9f;

	vector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	vector.y = sin(glm::radians(pitch)) * -1.0f;
	vector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	last_x_pos = x_pos;
	last_y_pos = y_pos;
	l_time = time;
}
