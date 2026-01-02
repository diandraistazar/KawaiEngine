#include "main.hpp"

float vertices[] = {
	0.6f, 0.6f, 0.0f,
	0.6f, -0.6f, 0.0f,
	-0.6f, -0.6f, 0.0f,
	
	-0.6f, -0.6f, 0.0f,
	-0.6f, 0.6f, 0.0f,
	0.6f, 0.6f, 0.0f,
};

VertexArray Graphic::VAO[V_TOTAL];
ShaderProgram Graphic::program;
Shader Graphic::vertex;
Shader Graphic::fragment;

int Graphic::setup(){
	int ret = 0;
	
	// Create VAO
	ret = Graphic::VAO[V_PLANE].create();
	if(ret){
		Debug::debugme(MSG_ERROR, "Graphic::setup::createVAO() returns RET_FAILURE");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Graphic::setup::createVAO() returns RET_SUCCESS");

	// Bind VAO
	Graphic::VAO[V_PLANE].bind(true);
	Graphic::VAO[V_PLANE].bind_buffer(GL_ARRAY_BUFFER, true);
	Graphic::VAO[V_PLANE].copydata(sizeof(vertices), vertices, GL_STATIC_DRAW);
	Graphic::VAO[V_PLANE].setpointer(0, 3, GL_FLOAT, 3 * sizeof(float), 0);
	Graphic::VAO[V_PLANE].enablepointer(0);

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
	Graphic::VAO[V_PLANE].bind(false);
	Graphic::VAO[V_PLANE].bind_buffer(GL_ARRAY_BUFFER, false);
	return RET_SUCCESS;
}

void Graphic::draw(){
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]) / 3);
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
