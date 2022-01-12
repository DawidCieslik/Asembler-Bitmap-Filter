#include "DLL_Cpp.h"
#include "pch.h"

void Filtration(unsigned char* input, unsigned char* output, int offset, int bytes_to_process, int width, int height)
{
    int y_min = offset / width;                             //Wysoko�� dolnej kraw�dzi przerabianego przez w�tek fragmentu
    int offset_x_low = offset % width;                        //Offset dolnej kraw�dzi przerabianego przez w�tek fragmentu
    int y_max = (offset + bytes_to_process) / width;        //Wysoko�� g�rnej kraw�dzi przerabianego przez w�tek fragmentu
    int offset_x_high = (offset + bytes_to_process) % width;  //Offset g�rnej kraw�dzi przerabianego przez w�tek fragmentu

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
            filter(input, output, width, x, y_min); //Filtrowanie dolnej kraw�dzi przerabianego przez w�tek fragmentu
        }
        y_min++;
    }

    for (int x = 3; x < offset_x_high; x += 3)
    {
        filter(input, output, width, x, y_max);     //Filtrowanie g�rnej kraw�dzi przerabianego przez w�tek fragmentu
    }

    for (int y = y_min; y < y_max; y++)
    {
        for (int x = 3; x < width - 3; x += 3)
        {
            filter(input, output, width, x, y);     //Filtrowanie pozosta�ej cz�ci przerabianego przez w�tek fragmentu
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