#include "main.hpp"
#include "shader.hpp"
#include "text_loader.hpp"
#include "debug.hpp"

int Shader::load(const char* filename, int shader_type){
	s_name = filename;
	id = glCreateShader(shader_type);
	if(!id){
		Debug::debugme(M_ERROR, "Shader::load::glCreateShader() %s: returns 0", s_name);
		return RET_FAILURE;
	}
	// load source code
	p_data = textloader::load(s_name);
	if(!p_data){
		Debug::debugme(M_ERROR, "Shader::load::load_text() %s: returns NULL", s_name);
		return RET_FAILURE;
	}
	const char *ptr = p_data;
	glShaderSource(id, 1, &ptr, nullptr);

	return RET_SUCCESS;
}

int Shader::compile(){
	int r_value = 0;
	
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &r_value);
	if(!r_value){
		char buffer[256] = {0};
		int buffer_size = 0;

		glGetShaderInfoLog(id, sizeof(buffer), &buffer_size, buffer);
		buffer[buffer_size-1] = '\0'; // remove newline from log
		
		Debug::debugme(M_ERROR, "Shader::compile::glCompileShader() %s : %s", s_name, buffer);
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

void Shader::delete_shader(){
	glDeleteShader(id);
	if(!p_data){
		Debug::debugme(M_ERROR, "Shader::delete_shader() %s : data is not exists or NULL", s_name);
		return;
	}
	textloader::free(p_data); p_data = nullptr;
	Debug::debugme(M_SUCCESS, "Shader::delete_shader() %s : data is SUCCESSFULLY to be free", s_name);
}
