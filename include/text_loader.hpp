#pragma once

// C++ Library to load Text File (.txt, .cpp, .c, something like that) as an array of bytes in memory main
#include <fstream>
#include <filesystem>

namespace filesystem = std::filesystem;
using std::ifstream;

struct textloader{
	static char *load(const char *filename){
		filesystem::path file_path = filename;
		ifstream file_stream(file_path);
	
		if(!file_stream.is_open())
			return nullptr;

		size_t file_size = filesystem::file_size(file_path);
		char *data = new char[file_size+1]; // +1 for null terminator
		file_stream.read(data, file_size);
		data[file_size] = '\0';

		file_stream.close();
		return data;
	}

	static void free(char *data){
		if(data)
			delete data;
	}
};
