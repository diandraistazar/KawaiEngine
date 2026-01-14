#pragma once

struct ShaderProgram{
	unsigned int id = -1;

	static void use(ShaderProgram &program, bool use);

	int create();
	void delete_prog();
	void attach(int shader);
	void link();
	void setUniform1i(const char *uniform_name, int value);
	void setUniform1f(const char *uniform_name, float value);
	void setUniformMatrix3fv(const char *uniform_name, float *matrix);
	void setUniformMatrix4fv(const char *uniform_name, float *matrix);
	void setUniform3fv(const char *uniform_name, float *vector);
};
