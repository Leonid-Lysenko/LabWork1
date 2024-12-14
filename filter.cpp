/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/
#include <vector>
#include "filter.h"

/*
-> The function below applies a filter to a single pixel in an image.
-> It takes a vector of pixels, the image dimensions, a filter kernel, and the pixel coordinates.
-> The function also calculates the filtered RGB values ​​by summing the weighted values ​​around the given pixel (defined by the kernel).
*/

void filterToPixel(const std::vector<unsigned char>& pix, int width, int height, const double core[5][5], int radius, int x, int y, std::vector<unsigned char>& filtpix)
{
    (void)height;
    double red = 0;
    double green = 0;
    double blue = 0;
    int offset = (x + (y * width)) * 3;

    for (int i = -radius; i <= radius; i++)
    {
        for (int j = -radius; j <= radius; j++)
        {
            int pixset = ((y + i) * width + (x + j)) * 3;
            double weight = core[i + radius][j + radius];
            red += (weight * pix[pixset]);
            green += (weight * pix[pixset + 1]);
            blue += (weight * pix[pixset + 2]);
        }
    }

    filtpix[offset] = static_cast<unsigned char>(red);
    filtpix[offset + 1] = static_cast<unsigned char>(green);
    filtpix[offset + 2] = static_cast<unsigned char>(blue);
}
