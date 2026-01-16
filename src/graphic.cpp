#include "main.hpp"
#include "graphic.hpp"
#include "input.hpp"
#include "debug.hpp"
#include <array>

// Verticies
std::array<float, 6*11> plane = {
//	Position					Color						Texture			Normal
	0.6f, 0.6f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
	0.6f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	-0.6f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	
	-0.6f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	-0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,
	0.6f, 0.6f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
};

std::array<float, 36*6> light_cube = {
//	Front
	0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,

	-0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,	0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,

// Back
	0.5f, 0.5f, -0.5f,	0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f,	0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f,	0.0f, 0.0f, -1.0f,

// Left
	-0.5f, 0.5f, 0.5f,	-1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,	-1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,	-1.0f, 0.0f, 0.0f,

// Right
	0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f,	1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,

	0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f,	1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,

// Top
	-0.5f, 0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,	0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f,	0.0f, 1.0f, 0.0f,
	
	0.5f, 0.5f, -0.5f,	0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,	0.0f, 1.0f, 0.0f,

// Bottom
	-0.5f, -0.5f, 0.5f,	0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,
	
	0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f,	0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,	0.0f, -1.0f, 0.0f,
};

VertexArray Graphic::VAO[VA_TOTAL];
VertexBuffer Graphic::VBO[VB_TOTAL];
ShaderProgram Graphic::program[PG_TOTAL];
Shader Graphic::shader[SH_TOTAL];
Texture Graphic::texture[TX_TOTAL];

int Graphic::setup(){
	// Create VAOs
	if(
		VAO[VA_PLANE].create() ||
		VAO[VA_LIGHT].create()
	){
		Debug::debugme(M_ERROR, "Graphic::setup::createVAO() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::createVAO() returns RET_SUCCESS");

	// Create VBOs
	if(
		VBO[VB_PLANE].create() ||
		VBO[VB_LIGHT].create()
	){
		Debug::debugme(M_ERROR, "Graphic::setup::createVBO() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::createVBO() returns RET_SUCCESS");
	
	// Bind VAO
	VertexArray::bind(VAO[VA_PLANE], true);
	VertexBuffer::bind(VBO[VB_PLANE], GL_ARRAY_BUFFER, true);
	VAO[VA_PLANE].store_vbo(VBO[VB_PLANE]);
	VBO[VB_PLANE].copy_data(plane.size() * sizeof(float), plane.data(), GL_STATIC_DRAW);
	VAO[VA_PLANE].set_pointer(0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO[VA_PLANE].set_pointer(1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO[VA_PLANE].set_pointer(2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO[VA_PLANE].set_pointer(3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VertexArray::enablepointer(0);
	VertexArray::enablepointer(1);
	VertexArray::enablepointer(2);
	VertexArray::enablepointer(3);
	
	VertexArray::bind(VAO[VA_LIGHT], true);
	VertexBuffer::bind(VBO[VB_LIGHT], GL_ARRAY_BUFFER, true);
	VAO[VA_LIGHT].store_vbo(VBO[VB_LIGHT]);
	VBO[VB_LIGHT].copy_data(light_cube.size() * sizeof(float), light_cube.data(), GL_STATIC_DRAW);
	VAO[VA_LIGHT].set_pointer(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VertexArray::enablepointer(0);

	VertexArray::bind(VAO[VA_TOTAL-1], false);
	VertexBuffer::bind(VBO[VB_TOTAL-1], GL_ARRAY_BUFFER, false);

	// Texture
	if(
		texture[TX_GRASS].create() || texture[TX_GRASS].load("texture/green-grass-texture.jpg")
	){
		Debug::debugme(M_ERROR, "Graphic::setup::loadtextures() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::loadtextures() returns RET_SUCCESS");

	Texture::activeTexture(GL_TEXTURE0);
	Texture::bind(texture[TX_GRASS], GL_TEXTURE_2D, true);
	texture[TX_GRASS].texture2D(0, GL_RGB, true);

	// Create shader and intialize
	if(
		shader[SH_VERTEX].load("shader/vertex.vert", GL_VERTEX_SHADER) ||
		shader[SH_FRAGMENT].load("shader/fragment.frag", GL_FRAGMENT_SHADER) ||
		shader[SH_LIGHT_VERT].load("shader/light.vert", GL_VERTEX_SHADER) ||
		shader[SH_LIGHT_FRAG].load("shader/light.frag", GL_FRAGMENT_SHADER)
	){
		Debug::debugme(M_ERROR, "Graphic::setup::loadshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::loadshaders() returns RET_SUCCESS");
	
	// Compiling shaders
	if(
		shader[SH_VERTEX].compile() || 
		shader[SH_FRAGMENT].compile() || 
		shader[SH_LIGHT_VERT].compile() ||
		shader[SH_LIGHT_FRAG].compile()
	){
		Debug::debugme(M_ERROR, "Graphic::setup::compileshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::compileshaders() returns RET_SUCCESS");

	// Create a program and attach shaders with it then linking
	if(
		program[PG_PROGRAM].create() || 
		program[PG_LIGHT].create()
	){
		Debug::debugme(M_ERROR, "Graphic::setup::program::create() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::program::create() returns RET_SUCCESS");
	
	program[PG_PROGRAM].attach(shader[SH_VERTEX].id);
	program[PG_PROGRAM].attach(shader[SH_FRAGMENT].id);
	program[PG_PROGRAM].link();

	program[PG_LIGHT].attach(shader[SH_LIGHT_VERT].id);
	program[PG_LIGHT].attach(shader[SH_LIGHT_FRAG].id);
	program[PG_LIGHT].link();

	// Delete Compiled Shaders after linking
	shader[SH_VERTEX].delete_shader();
	shader[SH_FRAGMENT].delete_shader();
	shader[SH_LIGHT_VERT].delete_shader();
	shader[SH_LIGHT_FRAG].delete_shader();
	
	// Delete texture from heap memory
	texture[TX_GRASS].free_image();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	return RET_SUCCESS;
}

void Graphic::terminate(){
	VertexArray::bind(VAO[VA_TOTAL-1], false);
	VertexBuffer::bind(VBO[VB_TOTAL-1], GL_ARRAY_BUFFER, false);
	ShaderProgram::use(program[PG_TOTAL-1], false);
	for(VertexArray &array : VAO){
		array.delete_array();
	}
	for(VertexBuffer &buffer : VBO){
		buffer.delete_buffer();
	}
	for(ShaderProgram &prog : program){
		prog.delete_prog();
	}
	for(Texture &tex : texture){
		tex.delete_texture();
	}
}

void Graphic::clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Draw Functions
void Graphic::draw_plane(glm::mat4 &eye){
	VAO[VA_PLANE].reset_matrix(1.0f);
	VAO[VA_PLANE].translate(0.0f, -0.5f, 0.0f);
	VAO[VA_PLANE].rotate(90.0f, 1.0f, 0.0f, 0.0f);
	VAO[VA_PLANE].scale(8.0f, 8.0f, 8.0f);
	glm::mat4 model = VAO[VA_PLANE].matrix;
	glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(model))); // M-1T = Mnormal

	ShaderProgram::use(program[PG_PROGRAM], true);
	program[PG_PROGRAM].setUniformMatrix4fv("matrix.model", glm::value_ptr(model));
	program[PG_PROGRAM].setUniformMatrix4fv("matrix.eye", glm::value_ptr(eye));
	program[PG_PROGRAM].setUniformMatrix3fv("matrix.normal", glm::value_ptr(normal));
	program[PG_PROGRAM].setUniform3fv("view.position", glm::value_ptr(Input::position));
	VertexArray::bind(VAO[VA_PLANE], true);
	glDrawArrays(GL_TRIANGLES, 0, VAO[VA_PLANE].get_verticies());
}

void Graphic::draw_light_cube(glm::mat4 &eye){
	VAO[VA_LIGHT].reset_matrix(1.0f);
	VAO[VA_LIGHT].translate(cos(glfwGetTime()), -0.1f, cos(glfwGetTime()));
	VAO[VA_LIGHT].scale(0.4f, 0.4f, 0.4f);
	glm::mat4 model = VAO[VA_LIGHT].matrix;

	struct{
		glm::vec3 position;
		glm::vec3 color;
		float radius;
		float ambient;
		float specular;
	} light;
	light.position = model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	light.color = glm::vec3(1.0f, 1.0f, 1.0f);
	light.radius = 0.24f * 10.0f;
	light.ambient = 0.065f;
	light.specular = 0.8f;
	
	ShaderProgram::use(program[PG_PROGRAM], true);
	program[PG_PROGRAM].setUniform3fv("light.position", glm::value_ptr(light.position));
	program[PG_PROGRAM].setUniform3fv("light.color", glm::value_ptr(light.color));
	program[PG_PROGRAM].setUniform1f("light.radius", light.radius);
	program[PG_PROGRAM].setUniform1f("light.ambient", light.ambient);
	program[PG_PROGRAM].setUniform1f("light.specular", light.specular);

	ShaderProgram::use(program[PG_LIGHT], true);
	program[PG_LIGHT].setUniformMatrix4fv("matrix.model", glm::value_ptr(model));
	program[PG_LIGHT].setUniformMatrix4fv("matrix.eye", glm::value_ptr(eye));
	program[PG_LIGHT].setUniform3fv("light.color", glm::value_ptr(light.color));
	VertexArray::bind(VAO[VA_LIGHT], true);
	glDrawArrays(GL_TRIANGLES, 0, VAO[VA_LIGHT].get_verticies());
}
