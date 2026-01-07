#define USE_DEBUG
#include "main.hpp"

void VertexArray::bind(VertexArray &array, bool use){
	unsigned int id_temp = 0;
	if(use)
		id_temp = array.getID();
	glBindVertexArray(id_temp);
}

void VertexArray::enablepointer(int location){
	glEnableVertexAttribArray(location);
}

int VertexArray::getID(){
	return id;
}

int VertexArray::getVerticies(){
	return buffer.size / sizeof(float) / buffer.vertex_size;
}

int VertexArray::create(float *data, int size){
	glGenVertexArrays(1, &id);
	glGenBuffers(1, &buffer.id);
	if(!id || !buffer.id){
		Debug::debugme(MSG_ERROR, "VertexArray::create() created an ID with zero value");
		return RET_FAILURE;
	}
	buffer.pointer = data;
	buffer.size = size;
	return RET_SUCCESS;
}

void VertexArray::deletearray(){
	glDeleteVertexArrays(1, &id);
	glDeleteBuffers(1, &buffer.id);
}

void VertexArray::bind_buffer(int target, bool use){
	unsigned int buffer_id_temp = 0;
	if(use){
		buffer_id_temp = buffer.id;
		buffer.target = target;
	}
	glBindBuffer(buffer.target, buffer_id_temp);
}

void VertexArray::setpointer(int location, int count, int type, int stride, void* offset){
	buffer.vertex_size += count;
	glVertexAttribPointer(location, count, type, GL_FALSE, stride, offset);
}

void VertexArray::copydata(int use){
	glBufferData(buffer.target, buffer.size, buffer.pointer, use);
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

void VertexArray::resetMatrix(float value){
	matrix *= glm::inverse(matrix);
}

glm::mat4 VertexArray::getMatrix(){
	return matrix;
}
