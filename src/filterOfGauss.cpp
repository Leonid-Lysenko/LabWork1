/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/

#include "bmpData.h"

/**
 * @brief Calculates the value of the Gaussian function at coordinates (x, y).
 * 
 * The formula used is:
 * \f[
 * \frac{1}{2 \pi \sigma^2} \exp\left(-\frac{x^2 + y^2}{2 \sigma^2}\right)
 * \f]
 * where \f$\sigma\f$ is the indicator parameter.
 * 
 * @param x X coordinate relative to kernel center.
 * @param y Y coordinate relative to kernel center.
 * @param indicator Standard deviation (sigma) of the Gaussian.
 * @return Gaussian function value at (x, y).
 */
double bmpData::GaussF(int x, int y, double indicator)
{
    return (1.0/(2* M_PI*pow(indicator, 2)))*exp(-(pow(x, 2) + pow(y, 2))/(2*pow(indicator, 2)));
}

/**
 * @brief Generates a Gaussian kernel matrix of given size and indicator.
 * 
 * The kernel is normalized so that the sum of all elements equals 1.
 * 
 * @param size Size of the kernel (must be odd).
 * @param indicator Standard deviation (sigma) of the Gaussian.
 * @return 2D vector representing the Gaussian kernel matrix.
 */
std::vector<std::vector<double>> bmpData::matrixOfCore(int size, double indicator)
{
    std::vector<std::vector<double>> core(size, std::vector<double>(size));
    double sum = 0.0;
    int midst = size/2;

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            core[x][y] = GaussF(x-midst, midst-y, indicator);
            sum += core[x][y];
        }
    }

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            core[x][y] /= sum;
        }
    }
    return core;
}

/**
 * @brief Applies the Gaussian kernel to a pixel at position (x, y).
 * 
 * This function performs convolution by multiplying neighboring pixels by kernel weights.
 * Pixel coordinates are clamped to image boundaries.
 * 
 * @param x X coordinate of the target pixel.
 * @param y Y coordinate of the target pixel.
 * @param core Gaussian kernel matrix.
 * @param midst Half of the kernel size (kernel center offset).
 * @param red Reference to accumulate the red channel value.
 * @param green Reference to accumulate the green channel value.
 * @param blue Reference to accumulate the blue channel value.
 */
void bmpData::pixCore(int x, int y, const std::vector<std::vector<double>>& core, int midst, double& red, double& green, double& blue)
{
    for (int l = -midst; l <= midst; l++)
    {
        for (int m = -midst; m <= midst; m++)
        {
            int pixX = x + m;
            int pixY = y + l;

            if (pixX < 0) pixX = 0;
            if (pixY < 0) pixY = 0;
            if (pixX >= width) pixX = width - 1;
            if (pixY >= height) pixY = height - 1;

            int pixIND1 = (pixY * (width * 3 + (4 - (width * 3) % 4) % 4) + pixX * 3);
            double weight = core[l + midst][m + midst];

            blue += pix[pixIND1] * weight;
            green += pix[pixIND1 + 1] * weight;
            red += pix[pixIND1 + 2] * weight;
        }
    }
}

/**
 * @brief Applies a Gaussian filter to the entire image.
 * 
 * The image is processed using multiple threads for performance.
 * 
 * @param sizeOfCore Size of the Gaussian kernel (should be odd).
 * @param indicator Standard deviation (sigma) of the Gaussian.
 * @param numThreads Number of threads to use for processing (default 4).
 */
void bmpData::filterOfGauss(int sizeOfCore, double indicator, int numThreads)
{
    std::vector<std::vector<double>> core = matrixOfCore(sizeOfCore, indicator);
    std::vector<uint8_t> filtpix(pix);

    int bmpPadd1 = (4 - (width * 3) % 4) % 4;
    int midst = sizeOfCore / 2;

    auto processSection = [&](int startY, int endY)
    {
        for (int y = startY; y < endY; y++)
        {
            for (int x = 0; x < width; x++)
            {
                double red = 0.0;
                double green = 0.0;
                double blue = 0.0;

                pixCore(x, y, core, midst, red, green, blue);

                int pixIND2 = (y * (width * 3 + bmpPadd1) + x * 3);

                filtpix[pixIND2] = static_cast<uint8_t>(blue);
                filtpix[pixIND2 + 1] = static_cast<uint8_t>(green);
                filtpix[pixIND2 + 2] = static_cast<uint8_t>(red);
            }
        }
    };

    std::vector<std::thread> threads;
    int rowsPerThread = height / numThreads;
    int remainingRows = height % numThreads;
    int startRow = 0;

    for (int i = 0; i < numThreads; ++i)
    {
        int endRow = startRow + rowsPerThread + (i < remainingRows ? 1 : 0);
        threads.emplace_back(processSection, startRow, endRow);
        startRow = endRow;
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    pix = std::move(filtpix);
}

