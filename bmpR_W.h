/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/
#ifndef BMPR_W_H
#define BMPR_W_H

#include <vector>
#include <string>
#include "bmpdata.h" // Include bmpdata structure definition

void bmpread(const std::string& fileName, std::vector<unsigned char>& pix, bmpdata& header);
void bmpwrite(const std::string& fileName, const std::vector<unsigned char>& pix, const bmpdata& header);

#endif // BMPR_W_H

