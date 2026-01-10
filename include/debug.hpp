#pragma once

#include <iostream>

namespace Debug{
	template<typename... Arg>
	static void debugme(int type, const char* string, Arg... args){
		char buffer[256] = {0};
		const char *strings[] = { 
			// GREEN	YELLOW		 RED		WHITE	
			"SUCCESS",  "WARNING",  "ERROR",    "INFO",
			"\e[32m",   "\e[33m",   "\e[31m",   "",
			
			// RESET
			"\e[0m"
		};
		std::FILE *output[] = { stdout, stdout, stderr, stdout };
		
		std::snprintf(buffer, sizeof(buffer), string, args...);
		std::fprintf(output[type], "%s-%s:%s[%s] = %s%s\n", PROGRAM, VERSION, strings[type+4], strings[type], buffer, strings[8]);
	}
}

