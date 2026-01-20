#pragma once

struct Shader{
	const char *s_name = nullptr;
	char *p_data = nullptr;
	unsigned int id = -1;

	int load(const char* filename, int shader_type);
	int compile();
	void delete_shader();
};
