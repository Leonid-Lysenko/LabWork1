/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/
#include <iostream>
#include <fstream>
#include "bmpR_W.h"

/*
-> The function below opens a BMP file for reading and reads the header into a bmpdata structure.
-> The width and height of the image are extracted, as well as the row size, taking alignment into account.
-> Memory is then allocated to store the pixels and the pixel data is read from the file.
*/

void bmpread(const std::string& fileName, std::vector<unsigned char>& pix, bmpdata& header)
{
    std::ifstream bmpfile(fileName, std::ios::binary);

    if (!bmpfile)
    {
        std::cerr << "Упс... Входной файл не получилось открыть :(" << std::endl;
        exit(1);
    }

    bmpfile.read(reinterpret_cast<char*>(&header), sizeof(header));

    int width = header.width;
    int height = header.height;

    int sizeLine = (width * header.bitsPerPix + 31) / 8;

    pix.resize(sizeLine * height);

    bmpfile.read(reinterpret_cast<char*>(pix.data()), pix.size());

    bmpfile.close();
}

/*
-> The function below opens a file for writing in binary mode and writes a header and pixel array to it.
-> If the file cannot be opened, an error message is printed.
*/

void bmpwrite(const std::string& fileName, const std::vector<unsigned char>& pix, const bmpdata& header)
{
    std::ofstream bmpfileOut(fileName, std::ios::binary);

    if (!bmpfileOut)
    {
        std::cerr << "Упс... Выходной файл не получилось открыть :(" << std::endl;
        exit(1);
    }

    bmpfileOut.write(reinterpret_cast<const char*>(&header), sizeof(header));
    bmpfileOut.write(reinterpret_cast<const char*>(pix.data()), pix.size());

    bmpfileOut.close();
}
