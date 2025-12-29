#ifndef TEXT_LOADER_H
#define TEXT_LOADER_H

// C/C++ Library to load Text File (.txt, .cpp, .c, something like that) as an array of bytes in memory main
enum ErrorValue { TEXT_LOADER_SUCCESS, TEXT_LOADER_CANNOT_LOAD, TEXT_LOADER_INVALID_ERROR, TEXT_LOADER_TOTAL };
#include <stdio.h>
#include <string.h>

int load_text(const char* filename, size_t Pdest_size, char* Pdest)
{
	FILE *file = NULL;
    int ch = -1, count = 0;
	
    file = fopen(filename, "r");
	if(!file || !Pdest)
		return TEXT_LOADER_CANNOT_LOAD;

    memset(Pdest, 0, Pdest_size);
    while((ch = fgetc(file)) != EOF && count < Pdest_size)
    {
        Pdest[count] = ch;
        count++;
    }

	fclose(file);
    return TEXT_LOADER_SUCCESS;
}

const char* error_to_string(int return_value)
{
    const char* strings[TEXT_LOADER_TOTAL] = { "TEXT_LOADER_SUCCESS", "TEXT_LOADER_CANNOT_LOAD", "TEXT_LOADER_INVALID_ERROR" };
    if(return_value < TEXT_LOADER_TOTAL)
        return strings[return_value];
    else
        return strings[TEXT_LOADER_INVALID_ERROR];
}

#endif
