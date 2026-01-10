#pragma once

#include "main.hpp"

struct Buffer{
	float *pointer = nullptr;
	unsigned int id = -1;
	unsigned int target = -1;
	unsigned int vertex_size = 0;
	int size = 0;
};

class VertexArray{
	unsigned int id = -1;
	Buffer buffer;
	glm::mat4 matrix;
	
	public:
	static void bind(VertexArray &array, bool use);
	static void enablepointer(int location);

	int getID();
	int getVerticies();
	int create(float *data, int size);
	void deletearray();
	void bind_buffer(int target, bool use);
	void setpointer(int location, int count, int type, int stride, void* offset);
	void copydata(int use);

	// For Transformation
	void scale(float x_scalar, float y_scalar, float z_scalar);
	void rotate(float degree, float around_x, float around_y, float around_z);
	void translate(float x, float y, float z);
	void resetMatrix(float value);
	glm::mat4 getMatrix();
};


