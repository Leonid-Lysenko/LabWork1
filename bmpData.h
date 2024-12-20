/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/

#ifndef BMPDATA_h
#define BMPDATA_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>

class bmpData
{
private:
#pragma pack(push, 1)
    struct HeaderBmp
    {
        uint16_t type = 0x4D42; // BMP file identifier
        uint32_t size = 0;      // BMP file size in bytes
        uint16_t reserved1 = 0;      // reserved field
        uint16_t reserved2 = 0;      // reserved field
        uint32_t offset = 54;   // image data offset in bytes from the beginning of the BMP file
    };

    struct HeaderBmpAdditInf
    {
        uint32_t dibHeaderSize = 40; // header size in bytes for the BMP file
        int32_t width = 0;          // image width in pixels
        int32_t height = 0;         // image height in pixels
        uint16_t numPlanes = 1; // number of color planes
        uint16_t bitsPerPix = 24; // number of bits per pixel
        uint32_t compression = 0; // compression type
        uint32_t imageSizeBytes = 0; // image size in bytes
        int32_t resForX = 0; // image resolution in pixels/meter along the abscissa axis (x)
        int32_t resForY = 0; // image resolution in pixels/meter along the ordinate axis (y)
        uint32_t numColors = 0; // number of colors
        uint32_t importantColors = 0; // number of important colors
    };
#pragma pack(pop)

    HeaderBmp headerFile;
    HeaderBmpAdditInf headerInf;

    std::vector<uint8_t> pix;
    std::vector<std::vector<double>> matrixOfCore(int size, double indicator);

    int width;
    int height;

    double GaussF(int x, int y, double indicator);
    void pixCore(int x, int y, const std::vector<std::vector<double>>& core, int midst, double& red, double& green, double& blue);

public:
    bmpData(const std::string& nameOfFile)
    {
        loadingFile(nameOfFile);
    }

    bool loadingFile(const std::string& nameOfFile);

    bool savingFile(const std::string& nameOfFile) const;

    void rotateRT();

    void rotateLF();

    void filterOfGauss(int sizeOfCore, double indicator);

};

#endif
