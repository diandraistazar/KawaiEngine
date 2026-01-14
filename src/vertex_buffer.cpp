#include "main.hpp"
#include "vertex_buffer.hpp"
#include "debug.hpp"

void VertexBuffer::bind(VertexBuffer &buffer, int target, bool use){
	unsigned int id_temp = 0;
	if(use){
		id_temp = buffer.id;
		buffer.target = target;
	}
	glBindBuffer(target, id_temp);
}

int VertexBuffer::create(){
	glGenBuffers(1, &id);
	if(!id){
		Debug::debugme(M_ERROR, "VertexBuffer::create() returns 0");
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

void VertexBuffer::delete_buffer(){
	glDeleteBuffers(1, &id);
	id = -1;
}

void VertexBuffer::copy_data(int data_size, float *data, int use){
	size = data_size;
	glBufferData(target, size, data, use);
}
