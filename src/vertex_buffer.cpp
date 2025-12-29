#include "main.hpp"

int VertexBuffer::create(){
	glGenBuffers(1, &id);
	if(!id){
		Debug::debugme(MSG_ERROR, "VertexBuffer::create() the Id is zero");
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

void VertexBuffer::deletebuffer(){
	glDeleteBuffers(1, &id);
}

void VertexBuffer::bind(int target, bool use){
	glBindBuffer(target, (use ? id : 0));
	c_target = target;
}

void VertexBuffer::storedata(size_t size, void *data, int usage){
	glBufferData(c_target, size, data, usage);
}
