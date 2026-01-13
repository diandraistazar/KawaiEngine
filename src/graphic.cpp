#include "main.hpp"
#include "graphic.hpp"
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

VertexArray Graphic::VAO[V_TOTAL];
VertexBuffer Graphic::VBO[V_TOTAL];
ShaderProgram Graphic::program, Graphic::light;
Shader Graphic::vertex, Graphic::light_vert;
Shader Graphic::fragment, Graphic::light_frag;
Texture Graphic::texture1;

int Graphic::setup(){
	int ret = 0;
	
	// Create VAOs
	ret = 0;
	ret |= VAO[V_PLANE].create();
	ret |= VAO[V_LIGHT].create();
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::createVAO() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::createVAO() returns RET_SUCCESS");

	// Create VBOs
	ret = 0;
	ret |= VBO[V_PLANE].create();
	ret |= VBO[V_LIGHT].create();
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::createVBO() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::createVBO() returns RET_SUCCESS");
	
	// Bind VAO
	VertexArray::bind(VAO[V_PLANE], true);
	VertexBuffer::bind(VBO[V_PLANE], GL_ARRAY_BUFFER, true);
	VAO[V_PLANE].store_vbo(VBO[V_PLANE]);
	VBO[V_PLANE].copy_data(plane.size() * sizeof(float), plane.data(), GL_STATIC_DRAW);
	VAO[V_PLANE].set_pointer(0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO[V_PLANE].set_pointer(1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO[V_PLANE].set_pointer(2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO[V_PLANE].set_pointer(3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VertexArray::enablepointer(0);
	VertexArray::enablepointer(1);
	VertexArray::enablepointer(2);
	VertexArray::enablepointer(3);
	
	VertexArray::bind(VAO[V_LIGHT], true);
	VertexBuffer::bind(VBO[V_LIGHT], GL_ARRAY_BUFFER, true);
	VAO[V_LIGHT].store_vbo(VBO[V_LIGHT]);
	VBO[V_LIGHT].copy_data(light_cube.size() * sizeof(float), light_cube.data(), GL_STATIC_DRAW);
	VAO[V_LIGHT].set_pointer(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VertexArray::enablepointer(0);

	VertexArray::bind(VAO[V_TOTAL-1], false);
	VertexBuffer::bind(VBO[V_TOTAL-1], GL_ARRAY_BUFFER, false);

	// Texture
	Texture::activeTexture(GL_TEXTURE0);
	ret = 0;
	ret |= texture1.create(GL_TEXTURE_2D, 0, GL_RGB, true, "texture/green-grass-texture.jpg");
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::loadtextures() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::loadtextures() returns RET_SUCCESS");
	
	// Create shader and intialize
	ret = 0;
	ret |= vertex.load("shader/vertex.vert", GL_VERTEX_SHADER);
	ret |= fragment.load("shader/fragment.frag", GL_FRAGMENT_SHADER);
	ret |= light_vert.load("shader/light.vert", GL_VERTEX_SHADER);
	ret |= light_frag.load("shader/light.frag", GL_FRAGMENT_SHADER);
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::loadshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::loadshaders() returns RET_SUCCESS");

	// Compiling shaders
	ret = 0;
	ret |= vertex.compile();
	ret |= fragment.compile();
	ret |= light_vert.compile();
	ret |= light_frag.compile();
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::compileshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::compileshaders() returns RET_SUCCESS");

	// Create a program and attach shaders with it then linking
	ret = 0;
	ret |= program.create();
	ret |= light.create();
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::program::create() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::program::create() returns RET_SUCCESS");
	
	program.attach(vertex.get_ID());
	program.attach(fragment.get_ID());
	program.link();

	light.attach(light_vert.get_ID());
	light.attach(light_frag.get_ID());
	light.link();

	// Delete Compiled Shaders after linking
	vertex.delete_shader();
	fragment.delete_shader();
	light_vert.delete_shader();
	light_frag.delete_shader();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	return RET_SUCCESS;
}

void Graphic::terminate(){
	ShaderProgram::use(program, false);
	program.delete_prog();
	light.delete_prog();
	texture1.delete_texture();
	VertexArray::bind(VAO[V_TOTAL-1], false);
	for(VertexArray &array : VAO){
		array.delete_array();
	}
	for(VertexBuffer &buffer : VBO){
		buffer.delete_buffer();
	}
}

void Graphic::clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Draw Functions
void Graphic::draw_plane(glm::mat4 &matrix){
	VAO[V_PLANE].reset_matrix(1.0f);
	VAO[V_PLANE].translate(0.0f, -0.5f, 0.0f);
	VAO[V_PLANE].rotate(90.0f, 1.0f, 0.0f, 0.0f);
	VAO[V_PLANE].scale(2.0f, 2.0f, 2.0f);
	glm::mat4 model = VAO[V_PLANE].get_matrix();
	glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(model))); // M-1T = Mnormal

	ShaderProgram::use(program, true);
	program.setUniformMatrix4fv("model", glm::value_ptr(model));
	program.setUniformMatrix4fv("matrix", glm::value_ptr(matrix));
	program.setUniformMatrix3fv("normal_matrix", glm::value_ptr(normal_matrix));
	VertexArray::bind(VAO[V_PLANE], true);
	glDrawArrays(GL_TRIANGLES, 0, VAO[V_PLANE].get_verticies());
}

void Graphic::draw_light_cube(glm::mat4 &matrix){
	VAO[V_LIGHT].reset_matrix(1.0f);
	VAO[V_LIGHT].rotate(glfwGetTime() * 180.0f / 3.14f, 0.0f, 1.0f, 0.0f);
	VAO[V_LIGHT].translate(1.0f, -0.5f + 0.12f, 0.0f);
	VAO[V_LIGHT].scale(0.2f, 0.2f, 0.2f);
	glm::mat4 model = VAO[V_LIGHT].get_matrix();

	struct Light{
		glm::vec3 position;
		glm::vec3 lighting;
	} source_light;
	source_light.position = model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	source_light.lighting = glm::vec3(1.0f, 1.0f, 1.0f) * (3.0f - (0.38f + source_light.position.y));

	ShaderProgram::use(program, true);
	program.setUniform3fv("light.position", glm::value_ptr(source_light.position));
	program.setUniform3fv("light.lighting", glm::value_ptr(source_light.lighting));

	ShaderProgram::use(light, true);
	light.setUniformMatrix4fv("model", glm::value_ptr(model));
	light.setUniformMatrix4fv("matrix", glm::value_ptr(matrix));
	light.setUniform3fv("light.lighting", glm::value_ptr(source_light.lighting));
	VertexArray::bind(VAO[V_LIGHT], true);
	glDrawArrays(GL_TRIANGLES, 0, VAO[V_LIGHT].get_verticies());
}
