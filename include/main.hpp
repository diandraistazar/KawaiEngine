#pragma once

#include <string>
#include <cstdio>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define PROGRAM "KawaiEngine"
#define VERSION "v1.0"

enum { RET_SUCCESS, RET_FAILURE };
enum { MSG_SUCCESS, MSG_WARNING, MSG_ERROR, MSG_INFO };
enum { V_PLANE, V_BOX, V_TOTAL };

class VertexArray{
glm::mat4 matrix;
unsigned int id = 0;
struct Buffer{
	unsigned int id = -1;
	unsigned int target = -1;
	unsigned int vertex_size = 0;
	float *pointer = nullptr;
	size_t size = 0;
}buffer;

public:
int getVerticies();
int create(float *data, size_t size);
void deletearray();
void setpointer(int location, int count, int type, int stride, void* offset);
void enablepointer(int location);
void bind(bool use);
void bind_buffer(int target, bool use);
void copydata(int use);

// For Transformation
void scale(float x_scalar, float y_scalar, float z_scalar);
void rotate(float degree, float around_x, float around_y, float around_z);
void translate(float x, float y, float z);
void resetMatrix(float value);
glm::mat4 getMatrix();
};

class Shader{
unsigned int id = 0;
char buffer[1024] = {0};

public:
int load(const char* filename, int shader_type);
int compile();
int deleteshader();
int getID();
};

class ShaderProgram{
unsigned int id = 0;

public:
int create();
void deleteprog();
void use(bool use);
void attach(int shader);
void link();
int getID();
};

#ifdef USE_DEBUG
namespace Debug{
	template<typename... Arg>
	static void debugme(int type, const char* string, Arg... args){
		std::FILE *output[] = { stdout, stdout, stderr, stdout };
		std::string strings[] = { 
			// GREEN	YELLOW		 RED		WHITE	
			"SUCCESS",  "WARNING",  "ERROR",    "INFO",
			"\e[32m",   "\e[33m",   "\e[31m",   "",
			
			// RESET
			"\e[0m"
		};
		char buffer[1024] = {0};
		std::snprintf(buffer, sizeof(buffer), string, args...);
		std::fprintf(output[type], "%s-%s:%s[%s] = %s%s\n", PROGRAM, VERSION, strings[type+4].c_str(), strings[type].c_str(), buffer, strings[8].c_str());
	}
	static void debugmatrix(float *matrix, int dimension){
		for(int index = 0; index < dimension; index++){
			if(index == 4 || index == 8 || index == 12)
				std::puts("");
			std::printf("%.1f ", matrix[index]);
		}
		std::puts("");
	}
}
#endif

namespace Display{
	extern int framerate;
	extern float frametime;

	void get_fps();
	void get_frametime();
}

namespace Window{
	extern GLFWwindow *window;
	extern int win_width;
	extern int win_height;

	int setup();
	int terminate();
	void looping();
}

namespace Graphic{
	extern VertexArray VAO[V_TOTAL];
	extern ShaderProgram program;
	extern Shader vertex, fragment;

	int setup();
	void draw(VertexArray &vertex);
	void clear();
	void transform(glm::mat4 &matrix);
}

namespace Input{
	extern float sensivity_pointer;
	extern float movement_speed;

	int setup();
	void get_movement(glm::vec3 &vector, glm::vec3 &direction);
	void get_direction(glm::vec3 &vector);
}

namespace Camera{
	extern float fov;
	extern float aspect_ratio;
	extern float near_plane;
	extern float far_plane;

	glm::mat4 view();
	glm::mat4 projection();
}
