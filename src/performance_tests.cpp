/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/

#include "performance_tests.h"
#include "bmpData.h"
#include <chrono>
#include <iostream>
#include <iomanip>

/**
 * @brief Runs performance tests for image rotation and Gaussian filtering.
 * 
 * Measures execution time for single-threaded and multi-threaded versions
 * of rotateRT, rotateLF, and filterOfGauss methods. Outputs average timings
 * and speedup factors over multiple runs.
 */
void run_performance_tests()
{
    const int runs = 5;
    
    // 1. Rotation performance testing
    {
        bmpData img("images/image.bmp");
        long long rtSingle = 0, rtMulti = 0;
        long long lfSingle = 0, lfMulti = 0;

        for (int i = 0; i < runs; ++i)
        {
            // Clockwise rotation single-threaded
            auto imgCopy = img;
            auto start = std::chrono::high_resolution_clock::now();
            imgCopy.rotateRT(1); // 1 thread
            auto end = std::chrono::high_resolution_clock::now();
            rtSingle += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            // Clockwise rotation multi-threaded
            imgCopy = img;
            start = std::chrono::high_resolution_clock::now();
            imgCopy.rotateRT(4); // 4 threads
            end = std::chrono::high_resolution_clock::now();
            rtMulti += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            // Counterclockwise rotation single-threaded
            imgCopy = img;
            start = std::chrono::high_resolution_clock::now();
            imgCopy.rotateLF(1);
            end = std::chrono::high_resolution_clock::now();
            lfSingle += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            // Counterclockwise rotation multi-threaded
            imgCopy = img;
            start = std::chrono::high_resolution_clock::now();
            imgCopy.rotateLF(4);
            end = std::chrono::high_resolution_clock::now();
            lfMulti += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }

        std::cout << "\n=== Rotation Performance Results ===\n";
        std::cout << "Clockwise Rotation:\n";
        std::cout << "- Single-thread: " << rtSingle / runs << " μs\n";
        std::cout << "- Multi-thread (4 threads): " << rtMulti / runs << " μs\n";
        std::cout << "- Improvement: " << std::fixed << std::setprecision(2) << static_cast<double>(rtSingle) / rtMulti << "x faster\n\n";

        std::cout << "Counter-clockwise Rotation:\n";
        std::cout << "- Single-thread: " << lfSingle / runs << " μs\n";
        std::cout << "- Multi-thread (4 threads): " << lfMulti / runs << " μs\n";
        std::cout << "- Improvement: " << std::fixed << std::setprecision(2) << static_cast<double>(lfSingle) / lfMulti << "x faster\n";
    }

    // 2. Gaussian filter performance testing
    {
        bmpData img("images/image.bmp");
        long long gaussSingle = 0, gaussMulti = 0;
        const int coreSize = 5;
        const double sigma = 5.0;

        for (int i = 0; i < runs; ++i)
        {
            auto imgCopy = img;
            auto start = std::chrono::high_resolution_clock::now();
            imgCopy.filterOfGauss(coreSize, sigma, 1);
            auto end = std::chrono::high_resolution_clock::now();
            gaussSingle += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            imgCopy = img;
            start = std::chrono::high_resolution_clock::now();
            imgCopy.filterOfGauss(coreSize, sigma, 4);
            end = std::chrono::high_resolution_clock::now();
            gaussMulti += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }

        std::cout << "\n=== Gaussian Filter Performance Results ===\n";
        std::cout << "Filter Parameters: " << coreSize << "x" << coreSize 
                  << " core, σ=" << sigma << "\n";
        std::cout << "- Single-thread: " << gaussSingle / runs << " μs\n";
        std::cout << "- Multi-thread (4 threads): " << gaussMulti / runs << " μs\n";
        std::cout << "- Improvement: " << std::fixed << std::setprecision(2) << static_cast<double>(gaussSingle) / gaussMulti << "x faster\n";

        // Calculate throughput in megapixels per second
        double mpixels = (static_cast<double>(img.width) * img.height) / 1e6;
        double singleThru = mpixels / (gaussSingle / runs * 1e-6);
        double multiThru = mpixels / (gaussMulti / runs * 1e-6);

        std::cout << "\nThroughput:\n";
        std::cout << "- Single-thread: ~" << std::setprecision(2) << singleThru << " MPixel/s\n";
        std::cout << "- Multi-thread: ~" << std::setprecision(2) << multiThru << " MPixel/s\n";
    }
}

