#pragma once

#include "main.hpp"
#include <iostream>
#include <array>

using std::fprintf, std::array, std::FILE, std::min;

enum { M_SUCCESS, M_WARNING, M_ERROR, M_INFO };

struct Debug{
	static const char *GetErrorString(){
		int error_value = glGetError();
		array<int, 2*4> i_flags = {
			GL_NO_ERROR, GL_INVALID_ENUM, GL_INVALID_VALUE, GL_INVALID_OPERATION,
			GL_INVALID_FRAMEBUFFER_OPERATION, GL_OUT_OF_MEMORY, GL_STACK_OVERFLOW
		};
		array<const char*, 2*4> s_flags = {
			"GL_NO_ERROR", "GL_INVALID_ENUM", "GL_INVALID_VALUE", "GL_INVALID_OPERATION",
			"GL_INVALID_FRAMEBUFFER_OPERATION", "GL_OUT_OF_MEMORY", "GL_STACK_OVERFLOW",

		};
		for(int index = 0; index < min(i_flags.size(), s_flags.size()); index++){
			if(error_value != i_flags[index])
				continue;
			return s_flags[index];
		}
		return nullptr;
	}
	template<typename... Arg>
	static void debugme(int type, const char *string, Arg... args){
		array<FILE*, 4> output = { stdout, stdout, stderr, stdout };
		array<const char*, 2*4> strings = { 
			"SUCCESS",  "WARNING",  "ERROR",    "INFO",
			"\e[32m",   "\e[33m",   "\e[31m",   "",
		};
		
		fprintf(output[type], PROGRAM "-" VERSION ":%s[%s] = ", strings[type+4], strings[type]);
		fprintf(output[type], string, args...);
		fprintf(output[type], "\e[0m\n"); // reset
	}
};
