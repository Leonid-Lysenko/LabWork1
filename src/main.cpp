/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/

#include "bmpData.h"
#include "performance_tests.h"
#include <chrono>
#include <iostream>

/**
 * @brief Main function that runs image processing operations and performance tests.
 * 
 * The program prompts the user for Gaussian filter parameters, runs performance tests,
 * loads an image, performs rotations and Gaussian filtering, and saves the results.
 * 
 * @return int Returns 0 on successful execution, -1 on failure to save images.
 */
int main()
{
    int sizeOfCore;    ///< Size of the Gaussian kernel (should be odd).
    double indicator;  ///< Standard deviation (sigma) for Gaussian filter.

    std::cout << "What size of the core you want for the Gaussian filter? Enter odd numbers! For example 5:   ";
    std::cin >> sizeOfCore;

    std::cout << "Please, enter the indicator for the Gaussian filter: for example 5.0:   ";
    std::cin >> indicator;

    /// Run performance tests before processing images.
    run_performance_tests();

    /// Load the original image.
    bmpData bmpImage("images/image.bmp");
    /// Create a copy of the original image for separate processing.
    bmpData otherImage = bmpImage;

    /// Rotate the first image 90 degrees to the right (clockwise).
    bmpImage.rotateRT(4);

    /// Save the rotated image.
    if (!bmpImage.savingFile("images/RT.bmp"))
    {
        std::cout << "Error. Image cannot be saved!" << std::endl;
        return -1;
    }
    std::cout << "Image rotated 90 degrees to the right. Saved in 'RT.bmp'!" << std::endl;

    /// Apply Gaussian filter to the rotated image.
    bmpImage.filterOfGauss(sizeOfCore, indicator, 4);

    /// Save the Gaussian filtered image.
    if (!bmpImage.savingFile("images/RT+GaussFilter.bmp"))
    {
        std::cout << "Error. Image cannot be saved!" << std::endl;
        return -1;
    }
    std::cout << "Gaussian filtered image saved: 'RT+GaussFilter.bmp'!" << std::endl;

    /// Rotate the second image 90 degrees to the left (counter-clockwise).
    otherImage.rotateLF(4);

    /// Save the rotated image.
    if (!otherImage.savingFile("images/LF.bmp"))
    {
        std::cout << "Error. Image cannot be saved!" << std::endl;
        return -1;
    }
    std::cout << "Image rotated 270 degrees to the right. Saved in 'LF.bmp'!" << std::endl;

    /// Apply Gaussian filter to the rotated image.
    otherImage.filterOfGauss(sizeOfCore, indicator, 4);

    /// Save the Gaussian filtered image.
    if (!otherImage.savingFile("images/LF+GaussFilter.bmp"))
    {
        std::cout << "Error saving image!" << std::endl;
        return -1;
    }
    std::cout << "Gaussian filtered image saved: 'LF+GaussFilter.bmp'!" << std::endl;

    return 0; ///< Successful program termination.
}

