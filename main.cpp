/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/
#include <iostream>
#include <vector>

#include "bmpdata.h"
#include "filter.h"
#include "bmpR_W.h"
#include "rotate.h"
#include "gaussian_filter.h"

/*
-> The function below is the main one. It reads and rotates the image clockwise and counterclockwise, respectively.
-> Also, a Gaussian filter is applied to both inverted images.
*/

int main()
{
    bmpdata header;

    std::vector<unsigned char> pix;



    // For clockwise rotation + Gaussian filter.

    bmpread("image.bmp", pix, header);

    rotateImageRight(pix, header.width, header.height);
    header.fileSize = sizeof(header) + pix.size();

    bmpwrite("right.bmp", pix, header);
    std::cout << "Файл image.bmp повернут на 90 градусов вправо и загружен в файл right.bmp!" << std::endl;

    filterOfGauss(pix, header.width, header.height);
    bmpwrite("rightGauss.bmp", pix, header);
    std::cout << "Фильтр Гаусса применен!" << std::endl;



    // For counter-clockwise rotation + Gaussian filter.

    bmpread("image.bmp", pix, header);

    rotateImageLeft(pix, header.width, header.height);
    header.fileSize = sizeof(header) + pix.size();

    bmpwrite("left.bmp", pix, header);
    std::cout << "Файл image.bmp повернут на 90 градусов влево и загружен в файл left.bmp!" << std::endl;

    filterOfGauss(pix, header.width, header.height);
    bmpwrite("leftGauss.bmp", pix, header);
    std::cout << "Фильтр Гаусса применен!" << std::endl;

    return 0;
}
