#define USE_DEBUG
#include "main.hpp"
#include <array>

std::array<float, 18> plane = {
	0.6f, 0.6f, 0.0f,
	0.6f, -0.6f, 0.0f,
	-0.6f, -0.6f, 0.0f,
	
	-0.6f, -0.6f, 0.0f,
	-0.6f, 0.6f, 0.0f,
	0.6f, 0.6f, 0.0f,
};

std::array<float, 54> box = {
	// Front
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	
	// Right
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,

	// Left
	0.0f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,

	// Back
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,


	// Bottom
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
};

VertexArray Graphic::VAO[V_TOTAL];
ShaderProgram Graphic::program;
Shader Graphic::vertex;
Shader Graphic::fragment;

int Graphic::setup(){
	int ret = 0;
	
	// Create VAO
	ret = Graphic::VAO[V_PLANE].create(plane.data(), plane.size() * sizeof(float));
	ret = Graphic::VAO[V_BOX].create(box.data(), box.size() * sizeof(float));
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::createVAO() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::createVAO() returns RET_SUCCESS");

	// Bind VAO
	Graphic::VAO[V_PLANE].bind(true);
	Graphic::VAO[V_PLANE].bind_buffer(GL_ARRAY_BUFFER, true);
	Graphic::VAO[V_PLANE].copydata(GL_STATIC_DRAW);
	Graphic::VAO[V_PLANE].setpointer(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	Graphic::VAO[V_PLANE].enablepointer(0);

	Graphic::VAO[V_BOX].bind(true);
	Graphic::VAO[V_BOX].bind_buffer(GL_ARRAY_BUFFER, true);
	Graphic::VAO[V_BOX].copydata(GL_STATIC_DRAW);
	Graphic::VAO[V_BOX].setpointer(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	Graphic::VAO[V_BOX].enablepointer(0);

	Graphic::VAO[V_BOX].bind(false);
	Graphic::VAO[V_BOX].bind_buffer(GL_ARRAY_BUFFER, false);

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
	ret = Graphic::vertex.deleteshader();
	ret = Graphic::fragment.deleteshader();
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::deleteshaders() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::deleteshaders() returns RET_SUCCESS");
	return RET_SUCCESS;
}

void Graphic::draw(VertexArray &vertex){
	glDrawArrays(GL_TRIANGLES, 0, vertex.getVerticies());
}

void Graphic::clear(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphic::transform(glm::mat4 &matrix){
	static int matrix_id = -1;
	if(matrix_id == -1)
		matrix_id = glGetUniformLocation(program.getID(), "matrix");
	glUniformMatrix4fv(matrix_id, 1, GL_FALSE, glm::value_ptr(matrix));
}
