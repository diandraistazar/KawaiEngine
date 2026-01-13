#include "main.hpp"
#include "vertex_array.hpp"
#include "debug.hpp"

void VertexArray::bind(VertexArray &array, bool use){
	unsigned int id_temp = 0;
	if(use)
		id_temp = array.get_ID();
	glBindVertexArray(id_temp);
}

void VertexArray::enablepointer(int location){
	glEnableVertexAttribArray(location);
}

int VertexArray::get_ID(){
	return id;
}

int VertexArray::get_verticies(){
	return p_buffer->get_size() / sizeof(float) / vertex_size;
}

int VertexArray::create(){
	glGenVertexArrays(1, &id);
	if(!id){
		Debug::debugme(M_ERROR, "VertexArray::create() created an ID with zero value");
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

void VertexArray::delete_array(){
	glDeleteVertexArrays(1, &id);
}

void VertexArray::set_pointer(int location, int count, int type, int stride, void* offset){
	vertex_size += count;
	glVertexAttribPointer(location, count, type, GL_FALSE, stride, offset);
}

void VertexArray::store_vbo(VertexBuffer &buffer){
	p_buffer = &buffer;
}

// For Transformation
void VertexArray::scale(float x_scalar, float y_scalar, float z_scalar){
	matrix = glm::scale(matrix, glm::vec3(x_scalar, y_scalar, z_scalar));
}

void VertexArray::rotate(float degree, float around_x, float around_y, float around_z){
	matrix = glm::rotate(matrix, glm::radians(degree), glm::vec3(around_x, around_y, around_z));
}

void VertexArray::translate(float x, float y, float z){
	matrix = glm::translate(matrix, glm::vec3(x, y, z));
}

void VertexArray::reset_matrix(float value){
	matrix *= glm::inverse(matrix);
}

glm::mat4 VertexArray::get_matrix(){
	return matrix;
}
