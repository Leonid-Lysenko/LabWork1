/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/
#include <vector>
#include "gaussian_filter.h"
#include "filter.h"

/*
-> The function below applies a Gaussian filter to the image.
-> A 5x5 filter (kernel) is declared, which is used to blur the image.
-> The filter is applied to every pixel except the edge pixels (to avoid potential issues with image processing accuracy and quality), using the filterToPixel function.
-> After processing, filtpix is ​​copied back to pix.
*/

void filterOfGauss(std::vector<unsigned char>& pix, int width, int height)
{
    double core[5][5] =
    {
        {0.0024, 0.0140, 0.0210, 0.0140, 0.0050},
        {0.0150, 0.0633, 0.0975, 0.0595, 0.0140},
        {0.0230, 0.0970, 0.1600, 0.0960, 0.0215},
        {0.0125, 0.0600, 0.0965, 0.0600, 0.0128},
        {0.0030, 0.0133, 0.0228, 0.0135, 0.0033}
    };

    int radius = 2;
    std::vector<unsigned char> filtpix(pix.size());

    for (int y = radius; y < height - radius; y++)
    {
        for (int x = radius; x < (width - radius); x++)
        {
            filterToPixel(pix, width, height, core, radius, x, y, filtpix);
        }
    }

    pix = filtpix;
}

