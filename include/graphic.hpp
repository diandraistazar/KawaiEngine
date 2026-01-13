#pragma once

#include "main.hpp"
#include "vertex_array.hpp"
#include "shader_program.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "glm_math.hpp"

enum { V_PLANE, V_LIGHT, V_TOTAL };

class Graphic{
	public:
	static VertexArray VAO[V_TOTAL];
	static VertexBuffer VBO[V_TOTAL];
	static ShaderProgram program, light;
	static Shader vertex, fragment, light_vert, light_frag;
	static Texture texture1;
	
	public:
	static int setup();
	static void terminate();
	static void clear();
	static void draw_plane(glm::mat4 &matrix);
	static void draw_light_cube(glm::mat4 &matrix);
};
