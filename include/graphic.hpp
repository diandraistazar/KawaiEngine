#pragma once

#include "main.hpp"
#include "vertex_array.hpp"
#include "shader_program.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Graphic{
	public:
	static VertexArray VAO[V_TOTAL];
	static ShaderProgram program, light;
	static Shader vertex, fragment, light_vert, light_frag;
	static Texture texture1;
	
	public:
	static int setup();
	static void cleanup();
	static void draw(VertexArray &vertex);
	static void clear();
};
