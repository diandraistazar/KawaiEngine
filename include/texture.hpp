#pragma once

struct Texture{
	unsigned char *data = nullptr;
	int target = -1;
	unsigned int id = -1;
	int img_w, img_h, comp;

	static void activeTexture(int unit);
	static void bind(Texture &texture, int target, bool use);

	int create();
	int load(const char *img_name);
	void texture2D(int base_level, int format, bool use_mipmap);
	void free_image();
	void delete_texture();
};

