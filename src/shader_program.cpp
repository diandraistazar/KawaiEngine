#define USE_DEBUG
#include "main.hpp"

int ShaderProgram::getID(){
	return id;
}

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

void ShaderProgram::setUniform1i(const char *uniform_name, int value){
	int location = glGetUniformLocation(id, uniform_name);
	if(location == -1)
		Debug::debugme(MSG_ERROR, "ShaderProgram::setUniform1i() cannot be found the \"%s\" uniform", uniform_name);
	else 
		glUniform1i(location, value);
}

void ShaderProgram::setUniformMatrix4fv(const char *uniform_name, float *matrix){
	int location = glGetUniformLocation(id, uniform_name);
	if(location == -1)
		Debug::debugme(MSG_ERROR, "ShaderProgram::setUniformMatrix4fv() cannot be found the \"%s\" uniform", uniform_name);
	else
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

