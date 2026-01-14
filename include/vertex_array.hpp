#pragma once

#include "main.hpp"
#include "vertex_buffer.hpp"
#include "glm_math.hpp"

struct VertexArray{
	unsigned int id = -1;
	VertexBuffer *p_buffer;
	int vertex_size = 0;
	glm::mat4 matrix;
	
	static void bind(VertexArray &array, bool use);
	static void enablepointer(int location);

	int get_verticies();

	int create();
	void delete_array();
	void set_pointer(int location, int count, int type, int stride, void* offset);
	void store_vbo(VertexBuffer &buffer);

	// For Transformation
	void scale(float x_scalar, float y_scalar, float z_scalar);
	void rotate(float degree, float around_x, float around_y, float around_z);
	void translate(float x, float y, float z);
	void reset_matrix(float value);
};
