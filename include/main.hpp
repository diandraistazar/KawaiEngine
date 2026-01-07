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
enum { V_PLANE, V_TRIANGLE, V_TOTAL };

struct Buffer{
	float *pointer = nullptr;
	unsigned int id = -1;
	unsigned int target = -1;
	unsigned int vertex_size = 0;
	int size = 0;
};

class VertexArray{
unsigned int id = -1;
Buffer buffer;
glm::mat4 matrix;

public:
static void bind(VertexArray &array, bool use);
static void enablepointer(int location);

int getID();
int getVerticies();
int create(float *data, int size);
void deletearray();
void bind_buffer(int target, bool use);
void setpointer(int location, int count, int type, int stride, void* offset);
void copydata(int use);

// For Transformation
void scale(float x_scalar, float y_scalar, float z_scalar);
void rotate(float degree, float around_x, float around_y, float around_z);
void translate(float x, float y, float z);
void resetMatrix(float value);
glm::mat4 getMatrix();
};

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

class Texture{
unsigned char *data = nullptr;
unsigned int id = -1;
int img_w, img_h, comp;

public:
static void activeTexture(int unit);

int create(int target, int base_level, int format, bool use_mipmap, const char* img_name);
void deletetexture();
};

#ifdef USE_DEBUG
namespace Debug{
	template<typename... Arg>
	static void debugme(int type, const char* string, Arg... args){
		char buffer[256] = {0};
		const char *strings[] = { 
			// GREEN	YELLOW		 RED		WHITE	
			"SUCCESS",  "WARNING",  "ERROR",    "INFO",
			"\e[32m",   "\e[33m",   "\e[31m",   "",
			
			// RESET
			"\e[0m"
		};
		std::FILE *output[] = { stdout, stdout, stderr, stdout };
		
		std::snprintf(buffer, sizeof(buffer), string, args...);
		std::fprintf(output[type], "%s-%s:%s[%s] = %s%s\n", PROGRAM, VERSION, strings[type+4], strings[type], buffer, strings[8]);
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
	extern Texture texture1;
	
	int setup();
	void cleanup();
	void draw(VertexArray &vertex);
	void clear();
}

namespace Input{
	extern float pitch, yaw;
	extern float sensivity_pointer;
	extern float movement_speed;
	extern glm::vec3 position, direction;

	int setup();
	void get_movement();
	void get_direction();
}

namespace Camera{
	extern float fov;
	extern float aspect_ratio;
	extern float near_plane;
	extern float far_plane;

	glm::mat4 view();
	glm::mat4 projection();
}
