#include "main.hpp"
#include "shader_program.hpp"
#include "debug.hpp"

void ShaderProgram::use(ShaderProgram &program, bool use){
	unsigned int id_temp = 0;
	if(use){
		id_temp = program.id;
	}
	glUseProgram(id_temp);
}

int ShaderProgram::create(){
	id = glCreateProgram();
	if(!id){
		Debug::debugme(M_ERROR, "ShaderProgram::create::glCreateShader() returns 0");
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

void ShaderProgram::delete_prog(){
	glDeleteProgram(id);
}

void ShaderProgram::attach(int shader){
	glAttachShader(id, shader);
}

void ShaderProgram::link(){
	glLinkProgram(id);
}

void ShaderProgram::setUniform1i(const char *uniform_name, int value){
	int location = glGetUniformLocation(id, uniform_name);
	if(location == -1)
		Debug::debugme(M_ERROR, "ShaderProgram::setUniform1i() cannot be found the \"%s\" uniform", uniform_name);
	else 
		glUniform1i(location, value);
}

void ShaderProgram::setUniform1f(const char *uniform_name, float value){
	int location = glGetUniformLocation(id, uniform_name);
	if(location == -1)
		Debug::debugme(M_ERROR, "ShaderProgram::setUniform1f() cannot be found the \"%s\" uniform", uniform_name);
	else
		glUniform1f(location, value);
}

void ShaderProgram::setUniformMatrix3fv(const char *uniform_name, float *matrix){
	int location = glGetUniformLocation(id, uniform_name);
	if(location == -1)
		Debug::debugme(M_ERROR, "ShaderProgram::setUniformMatrix3fv() cannot be found the \"%s\" uniform", uniform_name);
	else
		glUniformMatrix3fv(location, 1, GL_FALSE, matrix);
}

void ShaderProgram::setUniformMatrix4fv(const char *uniform_name, float *matrix){
	int location = glGetUniformLocation(id, uniform_name);
	if(location == -1)
		Debug::debugme(M_ERROR, "ShaderProgram::setUniformMatrix4fv() cannot be found the \"%s\" uniform", uniform_name);
	else
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void ShaderProgram::setUniform3fv(const char *uniform_name, float *vector){
	int location = glGetUniformLocation(id, uniform_name);
	if(location == -1)
		Debug::debugme(M_ERROR, "ShaderProgram::setUniform3fv() cannot be found the \"%s\" uniform", uniform_name);
	else
		glUniform3fv(location, 1, vector);
}
