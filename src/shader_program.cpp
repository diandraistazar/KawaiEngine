#include "main.hpp"

int ShaderProgram::create(){
	id = glCreateProgram();
	if(!id){
		Debug::debugme(MSG_ERROR, "ShaderProgram::create::glCreateShader() returns 0");
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

void ShaderProgram::deleteprog(){
	glDeleteProgram(id);
}

void ShaderProgram::attach(int shader){
	glAttachShader(id, shader);
}

void ShaderProgram::link(){
	glLinkProgram(id);
}

void ShaderProgram::use(bool use){
	glUseProgram( use ? id : 0 );
}
