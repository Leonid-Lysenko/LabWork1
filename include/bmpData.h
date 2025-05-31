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
#include <thread>
#include <mutex>
#include <functional>

/**
 * @class bmpData
 * @brief Class for handling BMP image data, including loading, saving, rotating, and applying Gaussian filter.
 */
class bmpData
{
private:
#pragma pack(push, 1)
    /**
     * @struct HeaderBmp
     * @brief Structure representing the BMP file header.
     */
    struct HeaderBmp
    {
        uint16_t type = 0x4D42;      ///< BMP file identifier
        uint32_t size = 0;           ///< BMP file size in bytes
        uint16_t reserved1 = 0;      ///< Reserved field
        uint16_t reserved2 = 0;      ///< Reserved field
        uint32_t offset = 54;        ///< Image data offset in bytes from the beginning of the BMP file
    };

    /**
     * @struct HeaderBmpAdditInf
     * @brief Structure representing the DIB header (additional BMP information).
     */
    struct HeaderBmpAdditInf
    {
        uint32_t dibHeaderSize = 40; ///< Header size in bytes for the BMP file
        int32_t width = 0;           ///< Image width in pixels
        int32_t height = 0;          ///< Image height in pixels
        uint16_t numPlanes = 1;      ///< Number of color planes
        uint16_t bitsPerPix = 24;    ///< Number of bits per pixel
        uint32_t compression = 0;    ///< Compression type
        uint32_t imageSizeBytes = 0; ///< Image size in bytes
        int32_t resForX = 0;         ///< Image resolution in pixels/meter along the X axis
        int32_t resForY = 0;         ///< Image resolution in pixels/meter along the Y axis
        uint32_t numColors = 0;      ///< Number of colors
        uint32_t importantColors = 0;///< Number of important colors
    };
#pragma pack(pop)

    HeaderBmp headerFile;                ///< BMP file header
    HeaderBmpAdditInf headerInf;         ///< BMP DIB header

    std::vector<uint8_t> pix;            ///< Pixel data
    /**
     * @brief Generates a Gaussian kernel matrix.
     * @param size Kernel size
     * @param indicator Gaussian indicator (sigma)
     * @return 2D vector representing the kernel
     */
    std::vector<std::vector<double>> matrixOfCore(int size, double indicator);

    int width;                           ///< Image width
    int height;                          ///< Image height

    /**
     * @brief Computes the value of the Gaussian function at (x, y).
     * @param x X coordinate
     * @param y Y coordinate
     * @param indicator Gaussian indicator (sigma)
     * @return Value of the Gaussian function
     */
    double GaussF(int x, int y, double indicator);

    /**
     * @brief Applies the convolution kernel to a pixel.
     * @param x X coordinate
     * @param y Y coordinate
     * @param core Convolution kernel
     * @param midst Kernel center
     * @param red Output red value
     * @param green Output green value
     * @param blue Output blue value
     */
    void pixCore(int x, int y, const std::vector<std::vector<double>>& core, int midst, double& red, double& green, double& blue);

public:
    /**
     * @brief Constructor. Loads BMP file.
     * @param nameOfFile Name of the BMP file to load
     */
    bmpData(const std::string& nameOfFile)
    {
        loadingFile(nameOfFile);
    }

    /**
     * @brief Loads BMP file.
     * @param nameOfFile Name of the BMP file to load
     * @return true if successful, false otherwise
     */
    bool loadingFile(const std::string& nameOfFile);

    /**
     * @brief Saves BMP file.
     * @param nameOfFile Name of the BMP file to save
     * @return true if successful, false otherwise
     */
    bool savingFile(const std::string& nameOfFile) const;
    
    /**
     * @brief Rotates the image to the right (clockwise).
     * @param numThreads Number of threads to use (default: 4)
     */
    void rotateRT(int numThreads = 4);
    
    /**
     * @brief Rotates the image to the left (counterclockwise).
     * @param numThreads Number of threads to use (default: 4)
     */
    void rotateLF(int numThreads = 4);

    /**
     * @brief Applies a Gaussian filter to the image.
     * @param sizeOfCore Size of the Gaussian kernel
     * @param indicator Gaussian indicator (sigma)
     * @param numThreads Number of threads to use (default: 4)
     */
    void filterOfGauss(int sizeOfCore, double indicator, int numThreads = 4);

    /**
     * @brief Friend function for running performance tests.
     */
    friend void run_performance_tests();
};

#endif

