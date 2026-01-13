#pragma once

class VertexBuffer{
	unsigned int id = -1;
	int c_target = -1;
	int size = 0;

	public:
	static void bind(VertexBuffer &buffer, int target, bool use);

	public:
	int get_ID();
	int get_size();
	void set_target(int target);

	public:
	int create();
	void delete_buffer();
	void copy_data(int data_size, float *data, int use);
};
