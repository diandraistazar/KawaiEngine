#pragma once

class Texture{
	unsigned char *data = nullptr;
	unsigned int id = -1;
	int img_w, img_h, comp;

	public:
	static void activeTexture(int unit);

	int create(int target, int base_level, int format, bool use_mipmap, const char* img_name);
	void delete_texture();
};

