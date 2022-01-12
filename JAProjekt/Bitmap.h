#pragma once

#include <Windows.h>
#include <string>
#include <fstream>

class Bitmap
{
	BITMAPFILEHEADER* file_header;
	BITMAPV5HEADER* info_header;
	unsigned char* pixels;
	int real_size;
	int allocated_size;

public:
	Bitmap()
	{
		file_header = NULL;
		info_header = NULL;
		pixels = NULL;
		real_size = 0;
		allocated_size = 0;
	}
	~Bitmap()
	{
		delete[] file_header;
		delete[] info_header;
		delete[] pixels;
	}

	BITMAPFILEHEADER* get_file_header() { return file_header; }
	BITMAPV5HEADER* get_info_header() { return info_header; }
	unsigned char* get_pixels() { return pixels; }
	int get_real_size() { return real_size; }
	int get_allocated_size() { return allocated_size; }

	void set_file_header(BITMAPFILEHEADER* fh) { file_header = fh; }
	void set_info_header(BITMAPV5HEADER* ih) { info_header = ih; }
	void set_pixels(unsigned char* p) { pixels = p; }
	void set_real_size(int rs) { real_size = rs; }
	void set_allocated_size(int as) { allocated_size = as; }

	bool load_bitmap(std::string& bitmap_path);
	void save_bitmap(std::string& output_path);
};