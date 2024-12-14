/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/
#include <vector>
#include "rotate.h"

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

/*
-> The function below rotates the image 90 degrees clockwise.
-> The function creates a new rotpix vector, into which the colors of the original image are copied, taking into account the new orientation.
-> After copying is complete, the original pixel array is replaced with a new one, and the width and height are swapped.
*/

void rotateImageRight(std::vector<unsigned char>& pix, int& width, int& height)
{
    std::vector<unsigned char> rotpix(pix.size());
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int srcSet = (y * width + x) * 3;
            int destSet = ((width - x - 1) * height + y) * 3;

            rotpix[destSet] = pix[srcSet];
            rotpix[destSet + 1] = pix[srcSet + 1];
            rotpix[destSet + 2] = pix[srcSet + 2];
        }
    }
    pix = rotpix;
    swap(width, height);
}

/*
-> The function below is similar to rotateImageRight, however it rotates the image 90 degrees counter-clockwise.
*/

void rotateImageLeft(std::vector<unsigned char>& pix, int& width, int& height)
{
    std::vector<unsigned char> rotpix(pix.size());
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int srcSet = (y * width + x) * 3;
            int destSet = (x * height + (height - y - 1)) * 3;

            rotpix[destSet] = pix[srcSet];
            rotpix[destSet + 1] = pix[srcSet + 1];
            rotpix[destSet + 2] = pix[srcSet + 2];
        }
    }
    pix = rotpix;
    swap(width, height);
}

