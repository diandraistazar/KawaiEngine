#pragma once

#include "main.hpp"
#include "vertex_array.hpp"
#include "shader_program.hpp"
#include "shader.hpp"
#include "texture.hpp"

enum VAOs { VA_PLANE, VA_LIGHT, VA_TOTAL };
enum VBOs { VB_PLANE, VB_LIGHT, VB_TOTAL };
enum PROGRAMs { PG_PROGRAM, PG_LIGHT, PG_TOTAL };
enum SHADERs { SH_VERTEX, SH_FRAGMENT, SH_LIGHT_VERT, SH_LIGHT_FRAG, SH_TOTAL };
enum TEXTUREs { TX_GRASS, TX_TOTAL };

struct Graphic{
	static VertexArray VAO[VA_TOTAL];
	static VertexBuffer VBO[VB_TOTAL];
	static ShaderProgram program[PG_TOTAL];
	static Shader shader[SH_TOTAL];
	static Texture texture[TX_TOTAL];
	
	static int setup();
	static void terminate();
	static void clear();
	static void draw_plane(glm::mat4 &eye);
	static void draw_light_cube(glm::mat4 &eye);
};
