#include "main.hpp"
#include "graphic.hpp"
#include "debug.hpp"
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
ShaderProgram Graphic::program, Graphic::light;
Shader Graphic::vertex, Graphic::light_vert;
Shader Graphic::fragment, Graphic::light_frag;
Texture Graphic::texture1;

int Graphic::setup(){
	int ret = 0;
	
	// Create VAO
	ret = Graphic::VAO[V_PLANE].create(plane.data(), plane.size() * sizeof(float));
	ret = Graphic::VAO[V_TRIANGLE].create(triangle.data(), triangle.size() * sizeof(float));
	ret = Graphic::VAO[V_LIGHT].create(light_cube.data(), light_cube.size() * sizeof(float));
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::createVAO() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::createVAO() returns RET_SUCCESS");

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
	Graphic::VAO[V_TRIANGLE].setpointer(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	Graphic::VAO[V_TRIANGLE].setpointer(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VertexArray::enablepointer(0);
	VertexArray::enablepointer(1);
	VertexArray::enablepointer(2);

	VertexArray::bind(Graphic::VAO[V_LIGHT], true);
	Graphic::VAO[V_LIGHT].bind_buffer(GL_ARRAY_BUFFER, true);
	Graphic::VAO[V_LIGHT].copydata(GL_STATIC_DRAW);
	Graphic::VAO[V_LIGHT].setpointer(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VertexArray::enablepointer(0);

	VertexArray::bind(Graphic::VAO[V_TOTAL-1], false);
	Graphic::VAO[V_TOTAL-1].bind_buffer(GL_ARRAY_BUFFER, false);

	// Texture
	Texture::activeTexture(GL_TEXTURE0);
	ret = texture1.create(GL_TEXTURE_2D, 0, GL_RGB, true, "textures/green-grass-texture.jpg");
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::loadtextures() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Graphic::program.setUniform1i("uTexture", 0);
	Debug::debugme(M_SUCCESS, "Graphic::setup::loadtextures() returns RET_SUCCESS");
	
	// Create shader and intialize
	ret = Graphic::vertex.load("shaders/vertex.vert", GL_VERTEX_SHADER);
	ret = Graphic::fragment.load("shaders/fragment.frag", GL_FRAGMENT_SHADER);
	ret = Graphic::light_vert.load("shaders/light.vert", GL_VERTEX_SHADER);
	ret = Graphic::light_frag.load("shaders/light.frag", GL_FRAGMENT_SHADER);
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::loadshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::loadshaders() returns RET_SUCCESS");

	// Compiling shaders
	ret = Graphic::vertex.compile();
	ret = Graphic::fragment.compile();
	ret = Graphic::light_vert.compile();
	ret = Graphic::light_frag.compile();
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::compileshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::compileshaders() returns RET_SUCCESS");

	// Create a program and attach shaders with it then linking
	ret = Graphic::program.create();
	ret = Graphic::light.create();
	if(ret){
		Debug::debugme(M_ERROR, "Graphic::setup::program::create() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Graphic::setup::program::create() returns RET_SUCCESS");
	Graphic::program.attach(vertex.getID());
	Graphic::program.attach(fragment.getID());
	Graphic::program.link();
	
	Graphic::light.attach(light_vert.getID());
	Graphic::light.attach(light_frag.getID());
	Graphic::light.link();

	// Delete Compiled Shaders after linking
	Graphic::vertex.deleteshader();
	Graphic::fragment.deleteshader();
	Graphic::light_vert.deleteshader();
	Graphic::light_frag.deleteshader();

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
