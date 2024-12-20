/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/

#include "bmpData.h"

// This function calculates the value of the Gaussian function for a given x, y, and indicator.
double bmpData::GaussF(int x, int y, double indicator)
{
    // The Gaussian formula: (1 / (2 * pi * indicator^2)) * exp(-(x^2 + y^2) / (2 * indicator^2)).
    return (1.0/(2* M_PI*pow(indicator, 2)))*exp(-(pow(x, 2) + pow(y, 2))/(2*pow(indicator, 2)));
}

// This function generates a Gaussian core matrix of the given size and indicator.
std::vector<std::vector<double>> bmpData::matrixOfCore(int size, double indicator)
{
    // Create a core matrix of the given size with double values.
    std::vector<std::vector<double>> core(size, std::vector<double>(size));

    // Initialize the sum and the middle point of the core matrix.
    double sum = 0.0;
    int midst = size/2;

    // Iterate over each element in the core matrix.
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            // Calculate the Gaussian value for the current position and add it to the sum.
            core[x][y] = GaussF(x-midst, midst-y, indicator);
            sum += core[x][y];
        }
    }

    // Iterate over each element in the core matrix again.
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            // Normalize the value by dividing it by the total sum of the Gaussian values.
            core[x][y] /= sum;
        }
    }
    // Return the generated Gaussian core matrix.
    return core;
}

// This function applies the filter core to a pixel at given x, y coordinates.
void bmpData::pixCore(int x, int y, const std::vector<std::vector<double>>& core, int midst, double& red, double& green, double& blue)
{
    // Iterate over the core matrix.
    for (int l = -(midst); l <= midst; l++)
    {
        for (int m = -(midst); m <= midst; m++)
        {
            // Calculate the coordinates of the neighboring pixel.
            int pixX = x+m;
            int pixY = y+l;

            // Clamp the pixel coordinates to the boundaries of the image.
            if (pixX < 0) pixX = 0;

            if (pixY < 0) pixY = 0;

            if (pixX >= width) pixX = width-1;

            if (pixY >= height) pixY = height-1;

            // Calculate the index of the neighboring pixel.
            int pixIND1 = (pixY * (width * 3 + (4 - (width * 3) % 4) % 4) + pixX * 3);

            // Get the weight from the core matrix.
            double weight = core[l + midst][m + midst];

            // Accumulate the weighted values for blue, green, and red channels.
            blue += pix[pixIND1]*weight;
            green += pix[pixIND1+1]*weight;
            red += pix[pixIND1+2]*weight;
        }
    }
}

// This function applies the Gaussian filter to the image.
void bmpData::filterOfGauss(int sizeOfCore, double indicator)
{
    // Generate the Gaussian core matrix.
    std::vector<std::vector<double>> core = matrixOfCore(sizeOfCore, indicator);
    // Create a new pixel vector to store the filtered pixel data.
    std::vector<uint8_t> filtpix(pix);

    // Calculate the padding for the image.
    int bmpPadd1 = (4-(width*3)%4)%4;
    // Calculate the middle point of the core matrix.
    int midst = sizeOfCore/2;

    // Iterate over each pixel in the image.
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Initialize the weighted values for blue, green, and red channels.
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;

            // Apply the core to the current pixel and accumulate weighted pixel values.
            pixCore(x, y, core, midst, red, green, blue);

            // Calculate the index of the current pixel.
            int pixIND2 = (y * (width * 3 + bmpPadd1) + x * 3);

            // Assign filtered values to the corresponding pixel in the filtered pixel vector.
            filtpix[pixIND2] = (uint8_t)(blue);
            filtpix[pixIND2+1] = (uint8_t)(green);
            filtpix[pixIND2+2] = (uint8_t)(red);
        }
    }
    // Move filtered pixel data to the original pixel data.
    pix = std::move(filtpix);
}
