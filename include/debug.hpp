#pragma once

#include "main.hpp"
#include <iostream>

enum { M_SUCCESS, M_WARNING, M_ERROR, M_INFO };

using std::fprintf, std::FILE;
struct Debug{
	template<typename... Arg>
	static void debugme(int type, const char *string, Arg... args){
		FILE *output[] = { stdout, stdout, stderr, stdout };
		const char *strings[] = { 
			// GREEN	YELLOW		 RED		WHITE	
			"SUCCESS",  "WARNING",  "ERROR",    "INFO",
			"\e[32m",   "\e[33m",   "\e[31m",   "",
			
			// RESET
			"\e[0m"
		};
		
		fprintf(output[type], "%s-%s:%s[%s] = ", PROGRAM, VERSION, strings[type+4], strings[type]);
		fprintf(output[type], string, args...);
		fprintf(output[type], "%s\n", strings[8]);
	}
	static const char *GetErrorString(){
		int flags[] = {
			GL_NO_ERROR, GL_INVALID_ENUM, GL_INVALID_VALUE, GL_INVALID_OPERATION,
			GL_INVALID_FRAMEBUFFER_OPERATION, GL_OUT_OF_MEMORY, GL_STACK_OVERFLOW
		};
		const char *s_flags[] = {
			"GL_NO_ERROR", "GL_INVALID_ENUM", "GL_INVALID_VALUE", "GL_INVALID_OPERATION",
			"GL_INVALID_FRAMEBUFFER_OPERATION", "GL_OUT_OF_MEMORY", "GL_STACK_OVERFLOW",

		};
		int flag_size = std::min(sizeof(flags)/sizeof(flags[0]), sizeof(s_flags)/sizeof(s_flags[0])); 
		int error_value = glGetError();
		for(int index = 0; index < flag_size; index++){
			if(error_value != flags[index])
				continue;
			return s_flags[index];
		}
		return nullptr;
	}
};
