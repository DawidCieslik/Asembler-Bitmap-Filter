#include "DLL_Cpp.h"
#include "pch.h"

void Filtration(unsigned char* input, unsigned char* output, int offset, int bytes_to_process, int width, int height)
{
    int y_min = offset / width;                             //Wysokoœæ dolnej krawêdzi przerabianego przez w¹tek fragmentu
    int offset_x_low = offset % width;                        //Offset dolnej krawêdzi przerabianego przez w¹tek fragmentu
    int y_max = (offset + bytes_to_process) / width;        //Wysokoœæ górnej krawêdzi przerabianego przez w¹tek fragmentu
    int offset_x_high = (offset + bytes_to_process) % width;  //Offset górnej krawêdzi przerabianego przez w¹tek fragmentu

    if (y_min == 0)
    {
        y_min = 1;
        offset_x_low = 0;
    }
    else if (y_min == height - 1)
    {
        return;
    }

    if (y_max == height - 1)
    {
        offset_x_high = 0;
    }
    else if (y_max == height)
    {
        y_max = height - 1;
        offset_x_high = 0;
    }

    if (offset_x_low != 0)
    {
        for (int x = offset_x_low; x < width - 3; x += 3)
        {
            filter(input, output, width, x, y_min); //Filtrowanie dolnej krawêdzi przerabianego przez w¹tek fragmentu
        }
        y_min++;
    }

    for (int x = 3; x < offset_x_high; x += 3)
    {
        filter(input, output, width, x, y_max);     //Filtrowanie górnej krawêdzi przerabianego przez w¹tek fragmentu
    }

    for (int y = y_min; y < y_max; y++)
    {
        for (int x = 3; x < width - 3; x += 3)
        {
            filter(input, output, width, x, y);     //Filtrowanie pozosta³ej czêœci przerabianego przez w¹tek fragmentu
        }
    }
}

void filter(unsigned char* input, unsigned char* output, int width, int x, int y, int color)
{
    int sumB = 0, sumG = 0, sumR = 0;
    for (int j = -color; j <= color; j += color)
    {
        for (int k = -1; k <= 1; k++)
        {
            sumB = sumB + input[(y - k) * width + (x - j)];
            sumG = sumG + input[(y - k) * width + (x - j) + 1];
            sumR = sumR + input[(y - k) * width + (x - j) + 2];
        }
    }
    output[y * width + x] = sumB / 9;
    output[y * width + x + 1] = sumG / 9;
    output[y * width + x + 2] = sumR / 9;
}