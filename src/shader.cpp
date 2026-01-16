#include "main.hpp"
#include "shader.hpp"
#include "text_loader.hpp"
#include "debug.hpp"

int Shader::load(const char* filename, int shader_type){
	name = filename;
	id = glCreateShader(shader_type);
	if(!id){
		Debug::debugme(M_ERROR, "Shader::load::glCreateShader() %s: returns 0", name);
		return RET_FAILURE;
	}
	// load source code
	data = textloader::load(name);
	if(!data){
		Debug::debugme(M_ERROR, "Shader::load::load_text() %s: returns NULL", name);
		return RET_FAILURE;
	}
	const char *ptr = data;
	glShaderSource(id, 1, &ptr, nullptr);

	return RET_SUCCESS;
}

int Shader::compile(){
	int ret = 0, buffer_size = 0;
	char buffer[1024] = {0};
	
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &ret);
	glGetShaderInfoLog(id, sizeof(buffer), &buffer_size, buffer);
	buffer[buffer_size-1] = '\0'; // remove newline from log
	if(!ret){
		Debug::debugme(M_ERROR, "Shader::compile::glCompileShader() %s: %s", name, buffer);
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

void Shader::delete_shader(){
	glDeleteShader(id);
	if(!data){
		Debug::debugme(M_ERROR, "Shader::delete_shader() %s : data is not exists or NULL", name);
		return;
	}
	textloader::free(data); data = nullptr;
	Debug::debugme(M_SUCCESS, "Shader::delete_shader() %s : data is SUCCESSFULLY to be free", name);
}
