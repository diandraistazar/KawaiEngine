#pragma once

struct VertexBuffer{
	unsigned int id = -1;
	int target = -1;
	int size = 0;

	static void bind(VertexBuffer &buffer, int target, bool use);

	int create();
	void delete_buffer();
	void copy_data(int data_size, float *data, int use);
};
