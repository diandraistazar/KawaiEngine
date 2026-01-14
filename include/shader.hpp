#pragma once

struct Shader{
	char buffer[1024] = {0};
	const char *name = nullptr;
	unsigned int id = -1;

	int load(const char* filename, int shader_type);
	int compile();
	void delete_shader();
};
