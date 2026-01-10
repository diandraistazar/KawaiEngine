#pragma once

#include "main.hpp"

class ShaderProgram{
	unsigned int id = -1;

	public:
	int getID();
	int create();
	void deleteprog();
	void use(bool use);
	void attach(int shader);
	void link();
	void setUniform1i(const char *uniform_name, int value);
	void setUniformMatrix4fv(const char *uniform_name, float *matrix);
};
