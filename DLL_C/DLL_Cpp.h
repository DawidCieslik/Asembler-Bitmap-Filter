#pragma once

#ifdef DLL_Cpp_EXPORTS
#define DLL_Cpp_API __declspec(dllexport)
#else
#define DLL_Cpp_API __declspec(dllimport)
#endif

extern "C" DLL_Cpp_API void Filtration(unsigned char* input, unsigned char* output, int offset, int bytes_to_process, int width, int height);

void filter(unsigned char* input, unsigned char* output, int width, int x, int y, int color = 3);