#define USE_DEBUG
#include "main.hpp"
#include "text_loader.hpp"

int Shader::load(const char* filename, int shader_type){
	name = filename;
	id = glCreateShader(shader_type);
	if(!id){
		Debug::debugme(MSG_ERROR, "Shader::load::glCreateShader() %s: returns 0", name);
		return RET_FAILURE;
	}
	// load source code
	int ret = load_text(name, sizeof(buffer), buffer);
	if(ret){
		Debug::debugme(MSG_ERROR, "Shader::load::load_text() %s: returns \"%s\"", error_to_string(ret), name);
		return RET_FAILURE;
	}
	
	const char* ptr = buffer;
	glShaderSource(id, 1, &ptr, nullptr);
	return RET_SUCCESS;
}

int Shader::compile(){
	int ret = 0;
	int buffer_size = 0;
	char buffer[1024] = {0};
	
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &ret);
	glGetShaderInfoLog(id, sizeof(buffer), &buffer_size, buffer);
	buffer[buffer_size-1] = '\0'; // remove newline from log
	if(!ret){
		Debug::debugme(MSG_ERROR, "Shader::compile::glCompileShader() %s: is FAILED to compile source code", name);
		Debug::debugme(MSG_ERROR, "Shader::compile::glCompileShader() %s: %s", name, buffer);
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

void Shader::deleteshader(){
	glDeleteShader(id);
}

int Shader::getID(){
	return id;
}
