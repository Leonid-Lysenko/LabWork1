/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/

#include "bmpData.h"

// This function loads a BMP file from the given filename.
bool bmpData::loadingFile(const std::string& nameOfFile)
{
    // Open the file in binary and input mode.
    std::ifstream file(nameOfFile, (std::ios::binary) | (std::ios::in));

    // Check if the file was opened successfully.
    if (!file.is_open())
    {
        std::cout<<"Error. File does not open!"<<std::endl;
        // If not, print an error message and return false.
        return false;
    }

    // Read the BMP file header.
    file.read((char*)&headerFile, sizeof(headerFile));

    // Check if the file is a valid BMP file by checking the header type.
    if (headerFile.type != 0x4D42)
    {
        std::cout<<"Hmm..., this is not a BMP file..."<<std::endl;
        // If not a BMP file, print an error message and return false.
        return false;
    }

    // Read the BMP header information.
    file.read((char*)&headerInf, sizeof(headerInf));

    // Extract the width and height from the header information.
    width = headerInf.width;
    height = headerInf.height;

    // Resize the pixel vector to the size specified in the header.
    pix.resize(headerInf.imageSizeBytes);

    // Move the file pointer to the beginning of the pixel data.
    file.seekg(headerFile.offset, std::ios::beg);
    // Read the pixel data into the pixel vector.
    file.read((char*)pix.data(), pix.size());

    // Close the file.
    file.close();

    // Return true to indicate successful loading.
    return true;
}


// This function saves the current image data to a BMP file with the given filename.
bool bmpData::savingFile(const std::string& nameOfFile) const
{
    // Open the file in binary and output mode.
    std::ofstream file(nameOfFile, std::ios::binary | std::ios::out);

    // Check if the file was opened successfully.
    if (!file.is_open())
    {
        std::cout<<"Error opening file for save it!"<<std::endl;
        // If not, print an error message and return false.
        return false;
    }

    // Create a new BMP file header with current image data.
    HeaderBmp headerFile =
    {
        0x4D42,  // Magic number for BMP file
        (uint32_t)(54 + pix.size()), // File size (header size + pixel data size)
        0,  // Reserved
        0,  // Reserved
        54
    }; // Offset to pixel data

    // Create a new BMP info header with current image data.
    HeaderBmpAdditInf headerInf =
    {
        40,  // Size of header info
        width,  // Image width
        height, // Image height
        1, // Color planes
        24, // Bits per pixel
        0, // Compression
        (uint32_t)pix.size(), // Image size
        0,  // Horizontal resolution
        0,  // Vertical resolution
        0,  // Number of colors in the palette
        0
    }; // Number of important colors used


    // Write the BMP file header to the file.
    file.write((const char*)&headerFile, sizeof(headerFile));

    // Write the BMP info header to the file.
    file.write((const char*)&headerInf, sizeof(headerInf));

    // Write the pixel data to the file.
    file.write((const char*)pix.data(), pix.size());

    // Close the file.
    file.close();

    // Return true to indicate successful saving.
    return true;
}


// This function rotates the image 90 degrees to the right (clockwise).
void bmpData::rotateRT()
{
    // Calculate the padding for the original and rotated image.
    int bmpPadd1 = (4-(width*3)%4)%4;
    int bmpPadd2 = (4-(height*3)%4)%4;

    // Create a new pixel vector for the rotated image.
    std::vector<uint8_t> rotpix((height * 3 + bmpPadd2) * width);

    // Iterate over each pixel in the original image.
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // Calculate the index for the source and destination pixels.
            int srcSet = (x*(width*3 + bmpPadd1)) + y*3;
            int destSet = ((height*3 + bmpPadd2))*(width - 1 - y) + x*3;

            // Copy the pixel data from the source to the destination vector.
            rotpix[destSet] = pix[srcSet];
            rotpix[destSet+1] = pix[srcSet+1];
            rotpix[destSet+2] = pix[srcSet+2];
        }
    }
    // Move the rotated pixel data to the original pixel vector.
    pix = std::move(rotpix);
    // Swap the width and height values to reflect the rotation.
    std::swap(height, width);
}


// This function rotates the image 90 degrees to the left (counter-clockwise).
void bmpData::rotateLF()
{
    // Calculate the padding for the original and rotated image.
    int bmpPadd1 = (4-(width*3)%4)%4;
    int bmpPadd2 = (4-(height*3)%4)%4;

    // Create a new pixel vector for the rotated image.
    std::vector<uint8_t> rotpix((height * 3 + bmpPadd2) * width);

    // Iterate over each pixel in the original image.
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // Calculate the index for the source and destination pixels.
            int srcSet = (x*(width*3 + bmpPadd1)) + y*3;
            int destSet = ((y*(height*3 + bmpPadd2)) + (height - 1 - x)*3);
            // Copy the pixel data from the source to the destination vector.
            rotpix[destSet] = pix[srcSet];
            rotpix[destSet+1] = pix[srcSet+1];
            rotpix[destSet+2] = pix[srcSet+2];
        }
    }

    // Move the rotated pixel data to the original pixel vector.
    pix = std::move(rotpix);
    // Swap the width and height values to reflect the rotation.
    std::swap(height, width);
}
