#include "main.hpp"

int VertexArray::create(){
	glGenVertexArrays(1, &id);
	if(!id){
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
	glBindVertexArray(use ? id : 0);
}
