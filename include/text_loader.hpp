#pragma once

// C++ Library to load Text File (.txt, .cpp, .c, something like that) as an array of bytes in memory main
enum ErrorValue { TEXT_LOADER_SUCCESS, TEXT_LOADER_CANNOT_LOAD, TEXT_LOADER_INVALID_ERROR, TEXT_LOADER_TOTAL };
#include <cstdio>
#include <memory>

int load_text(const char* filename, size_t dest_size, char* dest)
{
	if(!dest || dest_size < 0)
		return TEXT_LOADER_INVALID_ERROR;

	std::FILE *file = std::fopen(filename, "r");
	if(!file)
		return TEXT_LOADER_CANNOT_LOAD;

    std::memset(dest, 0, dest_size);
	int bytes = std::fread(dest, sizeof(char), dest_size, file);
	if(bytes < 1)
		return TEXT_LOADER_CANNOT_LOAD;

	std::fclose(file);
    return TEXT_LOADER_SUCCESS;
}

const char* error_to_string(int return_value)
{
    const char* strings[TEXT_LOADER_TOTAL] = { "TEXT_LOADER_SUCCESS", "TEXT_LOADER_CANNOT_LOAD", "TEXT_LOADER_INVALID_ERROR" };
    if(return_value >= 0 && return_value < TEXT_LOADER_TOTAL)
        return strings[return_value];
    return strings[TEXT_LOADER_INVALID_ERROR];
}
