/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/
#ifndef FILTER_H
#define FILTER_H

#include <vector>

void filterToPixel(const std::vector<unsigned char>& pix, int width, int height, const double core[5][5], int radius, int x, int y, std::vector<unsigned char>& filtpix);

#endif // FILTER_H

