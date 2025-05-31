/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/

#include "bmpData.h"

int main()
{
    // Variables to store the size of the core and indicator for Gaussian filter.
    int sizeOfCore;
    double indicator;

    // Prompt the user to enter the size of the core for the Gaussian filter.
    std::cout << "What size of thr core you want for the Gaussian filter? Enter odd numbers! for example 5:   ";
    std::cin >> sizeOfCore;
    // Prompt the user to enter the indicator for the Gaussian filter.
    std::cout << "Please, enter the indicatot for the Gaussian filter: for example 5.0:   ";
    std::cin >> indicator;

    // Load the image from "image.bmp"
    bmpData bmpImage("image.bmp");
    // Create a copy of the original image.
    bmpData otherImage = bmpImage;

    // Rotate the first image 90 degrees to the right.
    bmpImage.rotateRT();

    // Save the rotated image to "RT.bmp".
    if (!bmpImage.savingFile("RT.bmp"))
    {
        std::cout << "Error. Image cannot be saved!" << std::endl;
        return -1;
    }

    std::cout << "Image rotated 90 degrees to the right. Saved in 'RT.bmp'!" << std::endl;

    // Apply Gaussian filter to the rotated image.
    bmpImage.filterOfGauss(sizeOfCore, indicator);

    // Save the Gaussian filtered image.
    if (!bmpImage.savingFile("RT+GaussFilter.bmp"))
    {
        std::cout << "Error. Image cannot be saved!" << std::endl;
        return -1;
    }

    std::cout << "Gaussian filtered image saved: 'RT+GaussFilter.bmp'!" << std::endl;

    // Rotate the second image 90 degrees to the left.
    otherImage.rotateLF();
    // Save the rotated image.
    if (!otherImage.savingFile("LF.bmp"))
    {
        std::cout << "Error. Image cannot be saved!" << std::endl;
        return -1;
    }

    std::cout << "Image rotated 270 degrees to the right. Saved in 'LF.bmp'!" << std::endl;

    // Apply Gaussian filter to the rotated image.
    otherImage.filterOfGauss(sizeOfCore, indicator);

    // Save the Gaussian filtered image.
    if (!otherImage.savingFile("LT+GaussFilter.bmp"))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "Gaussian filtered image saved: 'LF+GaussFilter.bmp'!" << std::endl;

    // Program executed successfully
    return 0;
}
