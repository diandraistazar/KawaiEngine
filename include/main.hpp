#pragma once

#include <cstdint>
#include <cstdio>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define PROGRAM "KawaiEngine"
#define VERSION "v1.0"

enum { RET_SUCCESS, RET_FAILURE };
enum { MSG_SUCCESS, MSG_WARNING, MSG_ERROR, MSG_INFO };

struct VertexArray{
unsigned int id = 0;

int create();
void deletearray();
void setpointer(int location, int count, int type, int stride, int offset);
void enablepointer(int location);
void bind(bool use);
};

struct VertexBuffer{
unsigned int id = 0;
int c_target = 0;

int create();
void deletebuffer();
void bind(int target, bool use);
void storedata(size_t size, void *data, int usage);
};

struct Shader{
char *name = nullptr;
unsigned int id = 0;
char buffer[1024] = {0};

int load(const char* filename, int shader_type);
int compile();
int deleteshader();
};

struct ShaderProgram{
unsigned int id = 0;

int create();
void deleteprog();
void use(bool use);
void attach(int shader);
void link();
};

namespace Debug{
	template<typename... Arg>
	void debugme(int type, const char* string, Arg... args){
		std::FILE *output[] = { stdout, stdout, stderr, stdout };
		char *type_strings[] = { "SUCCESS", "WARNING", "ERROR", "INFO" };
		char *colors[] = { "\033[32m", "\033[33m", "\033[31m", "" };
		char *reset = "\033[0m";
		char buffer[1024] = {0};

		std::snprintf(buffer, sizeof(buffer), string, args...);
		std::fprintf(output[type], "%s-v%s:%s[%s] = %s%s\n", PROGRAM, VERSION, colors[type], type_strings[type], buffer, reset);
	}
}

namespace Window{
	int setup(); // Setup Window system
	int terminate(); // Terminate Window System
	void looping(); // Main Window Looping
}

namespace Graphic{
	extern VertexArray VAO;
	extern VertexBuffer VBO;
	extern ShaderProgram program;
	extern Shader vertex, fragment;

	int setup(); // Setup Graphic System
	void draw(); // draw stuffs on the screen
	void clear(); // clear previous framebuffer
}
