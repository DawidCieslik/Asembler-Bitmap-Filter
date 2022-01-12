#include "Bitmap.h"

bool Bitmap::load_bitmap(std::string& bitmap_path)
{
	std::ifstream input_file(bitmap_path, std::ios::binary);
	if (!input_file.is_open())
		return false;

	char* temp = new char[sizeof(BITMAPFILEHEADER)];
	input_file.read(temp, sizeof(BITMAPFILEHEADER));
	BITMAPFILEHEADER* file_header_p = (BITMAPFILEHEADER*)(temp);

	temp = new char[sizeof(BITMAPV5HEADER)];
	input_file.read(temp, sizeof(BITMAPV5HEADER));
	BITMAPV5HEADER* info_header_p = (BITMAPV5HEADER*)(temp);

	input_file.seekg(file_header_p->bfOffBits, std::ios::beg);

	int height = (int)info_header_p->bV5Height;
	int width = (int)info_header_p->bV5Width * 3;
	if (width % 4 != 0)					//Wyrównanie do 4 bajtów
		width += 4 - (width % 4);

	set_real_size(width * height);
	if (get_real_size() < 2048)			//Jeden w¹tek przerabia co najmniej 32 bajty
		set_allocated_size(2048);		//Potrzebne dla 64 w¹tków, aby nie by³o problemów w assemblerze
	else set_allocated_size(get_real_size());
	unsigned char* pixels = new unsigned char[get_allocated_size()];

	input_file.read((char*)pixels, get_real_size());

	set_file_header(file_header_p);
	set_info_header(info_header_p);
	set_pixels(pixels);

	input_file.close();
	return true;
}

void Bitmap::save_bitmap(std::string& output_path)
{
	std::ofstream output_file(output_path, std::ios::binary);
	if (output_file.is_open())
	{
		output_file.write((char*)get_file_header(), sizeof(BITMAPFILEHEADER));
		output_file.write((char*)get_info_header(), sizeof(BITMAPV5HEADER));
		output_file.write((char*)get_pixels(), get_real_size());
	}
	output_file.close();
}