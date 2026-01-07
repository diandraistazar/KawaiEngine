#define USE_DEBUG
#include "main.hpp"
#include <array>

std::array<float, 48> plane = {
//	Position			Color				Texture
	0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	0.6f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	-0.6f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	
	-0.6f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	-0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
};

std::array<float, 144> triangle = {
	// Front
	0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.5f, 1.0f,
	0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	
	// Right
	0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.5f, 1.0f,
	0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0, 0.0f,

	// Left
	0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.5f, 1.0f,
	-0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,	0.0f, 0.0f,

	// Back
	0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.5f, 1.0f,
	0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,	1.0f, 0.0f,

	// Bottom
	0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	
	-0.5f, -0.5f, -0.5f,0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
	0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
};

VertexArray Graphic::VAO[V_TOTAL];
ShaderProgram Graphic::program;
Shader Graphic::vertex;
Shader Graphic::fragment;
Texture Graphic::texture1;

int Graphic::setup(){
	int ret = 0;
	
	// Create VAO
	ret = Graphic::VAO[V_PLANE].create(plane.data(), plane.size() * sizeof(float));
	ret = Graphic::VAO[V_TRIANGLE].create(triangle.data(), triangle.size() * sizeof(float));
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::createVAO() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::createVAO() returns RET_SUCCESS");

	// Bind VAO
	VertexArray::bind(Graphic::VAO[V_PLANE], true);
	Graphic::VAO[V_PLANE].bind_buffer(GL_ARRAY_BUFFER, true);
	Graphic::VAO[V_PLANE].copydata(GL_STATIC_DRAW);
	Graphic::VAO[V_PLANE].setpointer(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	Graphic::VAO[V_PLANE].setpointer(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
	Graphic::VAO[V_PLANE].setpointer(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));
	VertexArray::enablepointer(0);
	VertexArray::enablepointer(1);
	VertexArray::enablepointer(2);

	VertexArray::bind(Graphic::VAO[V_TRIANGLE], true);
	Graphic::VAO[V_TRIANGLE].bind_buffer(GL_ARRAY_BUFFER, true);
	Graphic::VAO[V_TRIANGLE].copydata(GL_STATIC_DRAW);
	Graphic::VAO[V_TRIANGLE].setpointer(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	Graphic::VAO[V_TRIANGLE].setpointer(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
	Graphic::VAO[V_TRIANGLE].setpointer(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));
	VertexArray::enablepointer(0);
	VertexArray::enablepointer(1);
	VertexArray::enablepointer(2);

	VertexArray::bind(Graphic::VAO[V_TOTAL-1], false);
	Graphic::VAO[V_TRIANGLE].bind_buffer(GL_ARRAY_BUFFER, false);

	// Texture
	Texture::activeTexture(GL_TEXTURE0);
	ret = texture1.create(GL_TEXTURE_2D, 0, GL_RGB, true, "textures/green-grass-texture.jpg");
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::loadtextures() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Graphic::program.setUniform1i("uTexture", 0);
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::loadtextures() returns RET_SUCCESS");
	
	// Create shader and intialize
	ret = Graphic::vertex.load("shaders/vertex.vert", GL_VERTEX_SHADER);
	ret = Graphic::fragment.load("shaders/fragment.frag", GL_FRAGMENT_SHADER);
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::loadshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::loadshaders() returns RET_SUCCESS");

	// Compiling shaders
	ret = Graphic::vertex.compile();
	ret = Graphic::fragment.compile();
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::compileshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::compileshaders() returns RET_SUCCESS");

	// Create a program and attach shaders with it then linking
	ret = Graphic::program.create();
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::program::create() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::program::create() returns RET_SUCCESS");
	Graphic::program.attach(vertex.getID());
	Graphic::program.attach(fragment.getID());
	Graphic::program.link();
	
	// Delete Compiled Shaders after linking
	Graphic::vertex.deleteshader();
	Graphic::fragment.deleteshader();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	return RET_SUCCESS;
}

void Graphic::cleanup(){
	VertexArray::bind(Graphic::VAO[V_TOTAL-1], false);
	for(VertexArray &array : Graphic::VAO)
		array.deletearray();
	Graphic::program.use(false);
	Graphic::program.deleteprog();
	Graphic::texture1.deletetexture();
}

void Graphic::draw(VertexArray &vertex){
	glDrawArrays(GL_TRIANGLES, 0, vertex.getVerticies());
}

void Graphic::clear(){
	glClear(GL_COLOR_BUFFER_BIT);
}
