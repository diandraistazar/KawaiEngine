#include "main.hpp"

Object Model::object[V_TOTAL];

Object::Object(){
	glm::mat4 temp(1.0f);

	matrix = temp;
}

void Object::scale(float x_scalar, float y_scalar, float z_scalar){
	matrix = glm::scale(matrix, glm::vec3(x_scalar, y_scalar, z_scalar));
}

void Object::rotate(float degree, float around_x, float around_y, float around_z){
	matrix = glm::rotate(matrix, glm::radians(degree), glm::vec3(around_x, around_y, around_z));
}

void Object::translate(float x, float y, float z){
	matrix = glm::translate(matrix, glm::vec3(x, y, z));
}

glm::mat4 Object::getMatrix(){
	return matrix;
}
