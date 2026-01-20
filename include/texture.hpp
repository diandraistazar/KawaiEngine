#pragma once

struct Texture{
	unsigned char *p_data = nullptr;
	unsigned int id = -1;
	int target = -1;
	int img_w, img_h, comp;

	static void activeTexture(int unit);
	static void bind(Texture &texture, int target, bool use);

	int create();
	int load(const char *img_name);
	void texture2D(int base_level, int format, bool use_mipmap);
	void free_image();
	void delete_texture();
};

