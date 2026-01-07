#define USE_DEBUG
#include "main.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Texture::activeTexture(int unit){
	glActiveTexture(unit);
}

int Texture::create(int target, int base_level, int format, bool use_mipmap, const char* img_name){
	glGenTextures(1, &id);
	if(!id){
		Debug::debugme(MSG_ERROR, "Texture::create() ID returns zero");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Texture::create() ID returns non-zero");
	data = (unsigned char*)stbi_load(img_name, &img_w, &img_h, &comp, 0);
	if(!data){
		Debug::debugme(MSG_ERROR, "Texture::create() data returns NULL");
		return RET_FAILURE;
	}
	Debug::debugme(MSG_SUCCESS, "Texture::create() data returns non-NULL data");
	glBindTexture(target, id);
	glTexImage2D(target, base_level, format, img_w, img_h, 0, format, GL_UNSIGNED_BYTE, data);
	if(use_mipmap)
		glGenerateMipmap(target);
	stbi_image_free(data);
	Debug::debugme(MSG_SUCCESS, "Texture::create() image is SUCCESSFULLY to create");
	return RET_SUCCESS;
}

void Texture::deletetexture(){
	glDeleteBuffers(1, &id);
}
