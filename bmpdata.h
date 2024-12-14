/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/
#ifndef BMPDATA_H
#define BMPDATA_H

/*
-> The bmpdata structure defines the header of a BMP file.
-> It contains fields that describe the characteristics of the BMP, such as file size, image width and height, bits per pixel, and more.
-> #pragma pack(1) tells the compiler to pack the data without alignment.
*/

#pragma pack(push, 1)

struct bmpdata
{
    unsigned short type = 0x4D42; // BMP file identifier
    unsigned int fileSize = 0; // BMP file size in bytes
    unsigned short reserved1 = 0; // reserved field
    unsigned short reserved2 = 0; // reserved field
    unsigned int offset = 54; // image data offset in bytes from the beginning of the BMP file
    unsigned int dibHeaderSize = 40; // header size in bytes for the BMP file
    int width = 0; // image width in pixels
    int height = 0; // image height in pixels
    unsigned short numPlanes = 1; // number of color planes
    unsigned short bitsPerPix = 24; // number of bits per pixel
    unsigned int compression = 0; // compression type
    unsigned int imageSizeBytes = 0; // image size in bytes
    int resForX = 0; // image resolution in pixels/meter along the abscissa axis (x)
    int resForY = 0; // image resolution in pixels/meter along the ordinate axis (y)
    unsigned int numColors = 0; // number of colors
    unsigned int importantColors = 0; // number of important colors
};

#pragma pack(pop)

#endif // BMPDATA_H

