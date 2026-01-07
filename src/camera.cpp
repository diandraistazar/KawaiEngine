#include "main.hpp"

float Camera::fov = 60.0f;
float Camera::aspect_ratio = (float)Window::win_width/Window::win_height;
float Camera::near_plane = 0.1f;
float Camera::far_plane = 10.0f;

glm::mat4 Camera::view(){
	Input::get_direction(); Input::get_movement();
	return glm::lookAt(Input::position, Input::position + Input::direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::projection(){
	return glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);
}
