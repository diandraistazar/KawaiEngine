#include "main.hpp"

float vertices[] = {
	0.8f, -0.8f, 0.0f,
	-0.8f, -0.8f, 0.0f,
	0.0f, 0.8f, 0.0f,
};

VertexArray Graphic::VAO;
VertexBuffer Graphic::VBO;
ShaderProgram Graphic::program;
Shader Graphic::vertex;
Shader Graphic::fragment;

int Graphic::setup(){
	int ret = 0;
	
	// Create VAO, VBO
	ret = Graphic::VAO.create();
	ret = Graphic::VBO.create();
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::create_VAO_VBO() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::create_VAO_VBO() returns RET_SUCCESS");

	// Bind VAO and VBO
	Graphic::VAO.bind(true);
	Graphic::VBO.bind(GL_ARRAY_BUFFER, true);

	// Copy Data into VBO
	Graphic::VBO.storedata(sizeof(vertices), vertices, GL_STATIC_DRAW);
	Graphic::VAO.setpointer(0, 3, GL_FLOAT, 3 * sizeof(float), 0);
	Graphic::VAO.enablepointer(0);

	// Create shader and intialize
	ret = Graphic::vertex.load("shaders\\vertex.vert", GL_VERTEX_SHADER);
	ret = Graphic::fragment.load("shaders\\fragment.frag", GL_FRAGMENT_SHADER);
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
	Graphic::program.attach(vertex.id);
	Graphic::program.attach(fragment.id);
	Graphic::program.link();

	// Delete Compiled Shaders after linking
	ret = Graphic::vertex.deleteshader();
	ret = Graphic::fragment.deleteshader();
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::deleteshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::deleteshaders() returns RET_SUCCESS");
	Graphic::VAO.bind(false);
	Graphic::VBO.bind(GL_ARRAY_BUFFER, false);
	return RET_SUCCESS;
}

void Graphic::draw(){
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]) / 3);
}

void Graphic::clear(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
