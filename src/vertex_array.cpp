#include "main.hpp"

int VertexArray::create(){
	glGenVertexArrays(1, &id);
	glGenBuffers(1, &buffer_id);
	if(!id || !buffer_id){
		Debug::debugme(MSG_ERROR, "VertexArray::create() created an Id with zero value");
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

void VertexArray::deletearray(){
	glDeleteVertexArrays(1, &id);
}

void VertexArray::setpointer(int location, int count, int type, int stride, int offset){
	glVertexAttribPointer(location, count, type, GL_FALSE, stride, (void*)(offset));
}

void VertexArray::enablepointer(int location){
	glEnableVertexAttribArray(location);
}

void VertexArray::bind(bool use){
	unsigned int id_temp = 0;
	if(use)
		id_temp = id;
	glBindVertexArray(id_temp);
}

void VertexArray::bind_buffer(int target, bool use){
	unsigned int buffer_id_temp = 0;
	if(use)
		buffer_id_temp = buffer_id;
	c_target = target;
	glBindBuffer(c_target, buffer_id_temp);
}

void VertexArray::copydata(size_t data_size, float *data, int use){
	glBufferData(c_target, data_size, data, use);
}
