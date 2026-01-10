#pragma once

#include "main.hpp"

class Shader{
	char buffer[1024] = {0};
	const char *name = nullptr;
	unsigned int id = -1;

	public:
	int load(const char* filename, int shader_type);
	int compile();
	void deleteshader();
	int getID();
};
