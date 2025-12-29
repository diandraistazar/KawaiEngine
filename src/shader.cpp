#include "main.hpp"
#include "text_loader.h"

int Shader::load(const char* filename, int shader_type){
	name = (char*)filename;
	id = glCreateShader(shader_type);
	if(!id){
		Debug::debugme(MSG_ERROR, "Shader::load::glCreateShader() returns 0");
		return RET_FAILURE;
	}
	// load source code
	int ret = load_text(name, sizeof(buffer), buffer);
	if(ret){
		Debug::debugme(MSG_ERROR, "Shader::load::load_text() returns \"%s\"", error_to_string(ret));
		return RET_FAILURE;
	}
	
	const char* ptr = buffer;
	glShaderSource(id, 1, &ptr, nullptr);
	return RET_SUCCESS;
}

int Shader::compile(){
	int ret = 0;
	
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &ret);
	if(!ret){
		Debug::debugme(MSG_ERROR, "Shader::compile::glCompileShader() is FAILED to compile \"%s\" source code", name);
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

int Shader::deleteshader(){
	if(!id){
		Debug::debugme(MSG_ERROR, "Shader::deleteshader() the Shader Id is 0");
		return RET_FAILURE;
	}
	glDeleteShader(id);
	id = 0;
	return RET_SUCCESS;
}
