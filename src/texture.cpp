#include "main.hpp"
#include "texture.hpp"
#include "debug.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Texture::activeTexture(int unit){
	glActiveTexture(unit);
}

void Texture::bind(Texture &texture, int target, bool use){
	unsigned int id_temp = 0;
	if(use){
		id_temp = texture.id;
		texture.target = target;
	}
	glBindTexture(target, id_temp);
}

int Texture::create(){
	glGenTextures(1, &id);
	if(!id){
		Debug::debugme(M_ERROR, "Texture::create() ID returns zero");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Texture::create() ID returns non-zero");
	return RET_SUCCESS;
}

int Texture::load(const char *img_name){
	data = (unsigned char*)stbi_load(img_name, &img_w, &img_h, &comp, 0);
	if(!data){
		Debug::debugme(M_ERROR, "Texture::create() data returns NULL");
		return RET_FAILURE;
	}
	Debug::debugme(M_SUCCESS, "Texture::create() data returns non-NULL data");
	return RET_SUCCESS;
}

void Texture::texture2D(int base_level, int format, bool use_mipmap){
	glTexImage2D(target, base_level, format, img_w, img_h, 0, format, GL_UNSIGNED_BYTE, data);
	if(use_mipmap)
		glGenerateMipmap(target);
}

void Texture::free_image(){
	stbi_image_free(data);
}

void Texture::delete_texture(){
	glDeleteBuffers(1, &id);
}
