/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/

#include <iostream>
#include <fstream>
#include <vector>



/*
-> Структура bmpdata определяет заголовок BMP-файла.
-> Она содержит поля, которые описывают характеристики BMP, такие как размер файла, ширина и высота изображения, количество бит на пиксель и другие.
-> #pragma pack(1) указывает компилятору упаковывать данные без выравнивания.
*/

#pragma pack(1)

struct bmpdata
{
    uint16_t type = 0x4D42;  // идентификатор BMP-файла
    uint32_t fileSize = 0;    // размер BMP-файла в байтах
    uint16_t reserved1 = 0; // зарезервированое поле
    uint16_t reserved2 = 0; // зарезервировано поле
    uint32_t offset = 54; // смещение данных изображения в байтах от начала BMP-файла
    uint32_t dibHeaderSize = 40; // размер заголовка в байтах для BMP-файла
    int32_t width = 0;// ширина изображения в пикселях
    int32_t height = 0; // высота изображения в пикселях
    uint16_t numPlanes = 1;// количество цветовых плоскостей
    uint16_t bitsPerPix = 24;// количество бит на пиксель
    uint32_t compression = 0;// тип сжатия
    uint32_t imageSizeBytes = 0; // размер изображения в байтах
    int32_t resForX = 0; // разрешение изображения пиксель/метр вдоль оси абсцисс (х)
    int32_t resForY = 0; // разрешение изображения пиксель/метр вдоль оси ординат (у)
    uint32_t numColors = 0; // количество цветов
    uint32_t importantColors = 0; // количество важных цветов
};

#pragma pack(push, f)
#pragma pack(pop)  



/*
-> Функция ниже применяет фильтр к отдельному пикселю изображения.
-> Она принимает вектор пикселей, размеры изображения, ядро фильтра и координаты пикселя.
-> Помимо этого функция вычисляет отфильтрованные значения RGB, суммируя взвешенные значения вокруг данного пикселя (определяемого ядром).
*/
void filterToPixel(const std::vector<unsigned char>& pix, int width, int height, const double core[5][5], int radius, int x, int y, std::vector<unsigned char>& filtpix)
{
    double red = 0; double green = 0; double blue = 0; int offset = (x + (y * width))*3;
    for (int i = -(radius); i <= radius; i++)
    {
        for (int j = -(radius); j <= radius; j++)
        {
            int pixset = ((y + i) * width + (x + i))*3;
            double weight = core[i + radius][j + radius];
            red += (weight * pix[pixset]);
            green += (weight * pix[pixset+1]);
            blue += (weight * pix[pixset+2]);
        }
    }
    filtpix[offset] = static_cast<unsigned char>(red);
    filtpix[offset+1] = static_cast<unsigned char>(green);
    filtpix[offset+2] = static_cast<unsigned char>(blue);
}




/*
-> Функция ниже открывает BMP-файл для чтения и считывает заголовок в структуру bmpdata.
-> Извлекается ширина и высота изображения, а также размер строки с учетом выравнивания.
-> Затем выделяется память для хранения пикселей и считываются данные пикселей из файла.
*/
void bmpread(const std::string& fileName, std::vector<unsigned char>& pix, bmpdata& header)
{
    std::ifstream bmpfile(fileName, std::ios::binary);
    
    if (not(bmpfile)) {std::cerr<<"Упс... Входной файл не получилось открыть :("<<std::endl; exit(1);}

    bmpfile.read(reinterpret_cast<char*>(&header), sizeof(header));

    int width = header.width; int height = header.height;
    
    int sizeLine = (width * header.bitsPerPix+31)/8;

    pix.resize(sizeLine * height);

    bmpfile.read(reinterpret_cast<char*>(pix.data()), pix.size());
    
    bmpfile.close();
}



/*
-> Функция ниже открывает файл для записи в двоичном режиме и записывает в него заголовок и массив пикселей.
-> Если файл не удается открыть, выводится сообщение об ошибке.
*/
void bmpwrite(const std::string& fileName,  const std::vector<unsigned char>& pix, const bmpdata& header)
{
    std::ofstream bmpfileOut(fileName, std::ios::binary);
    
    if (not(bmpfileOut)) {std::cerr<<"Упс... Выходной файл не получилось открыть :("<<std::endl; exit(1);}

    bmpfileOut.write(reinterpret_cast<const char*>(&header), sizeof(header));

    bmpfileOut.write(reinterpret_cast<const char*>(pix.data()), pix.size());
    
    bmpfileOut.close();
}


/*
-> Функция ниже поворачивает изображение на 90 градусов по часовой стрелке.
-> Функция создает новый вектор rotpix, в который копируются цвета исходного изображения с учётом новой ориентации.
-> После окончания копирования исходный массив пикселей заменяется на новый, а ширина и высота меняются местами.
*/
void rotateImageRight(std::vector<unsigned char>& pix, int& width, int& height)
{
    std::vector<unsigned char> rotpix(pix.size());
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int srcSet = (y * width + x)*3;
            int destSet = ((width - x - 1) * height + y)*3;

            rotpix[destSet] = pix[srcSet];
            rotpix[destSet+1] = pix[srcSet+1];
            rotpix[destSet+2] = pix[srcSet+2];
        }
    }
    pix = rotpix;
    std::swap(width, height);
}



/*
-> Функция ниже аналогична функции rotateImageRight, однако она поворачивает изображение на 90 градусов против часовой стрелки.
*/
void rotateImageLeft(std::vector<unsigned char>& pix, int& width, int& height)  
{  
    std::vector<unsigned char> rotpix(pix.size());
    for (int x = 0; x < width; x++)  
    {  
        for (int y = 0; y < height; y++)  
        {  
            int srcSet = (y * width + x)*3;
            int destSet = (x * height + (height - y - 1))*3;  

            rotpix[destSet] = pix[srcSet];
            rotpix[destSet+1] = pix[srcSet+1];
            rotpix[destSet+2] = pix[srcSet+2]; 
        }  
    }  
    pix = rotpix;
    std::swap(width, height);
}  



/*
-> Функция ниже применяет фильтр Гаусса к изображению.
-> Объявлен фильтр (ядро) размером 5x5, который используется для размытия изображения.
-> Фильтр применяется к каждому пикселю, кроме краевых (во избежание потенциальных проблем с точностью и качеством обработки изображения), с помощью функции filterToPixel.
-> После обработки filtpix копируются обратно в pix.
*/
void filterOfGauss(std::vector<unsigned char>& pix, int width, int height)
{
    double core[5][5] = {{0.0024, 0.0140, 0.0210, 0.0140, 0.0050}, {0.0150, 0.0633, 0.0975, 0.0595, 0.0140}, {0.0230, 0.0970, 0.1600, 0.0960, 0.0215}, {0.0125, 0.0600, 0.0965, 0.0600, 0.0128}, {0.0030, 0.0133, 0.0228, 0.0135, 0.0033}};
    int radius = 2;
    std::vector<unsigned char>filtpix(pix.size());
    for (int y = radius; y < height - radius; y++)
    {
        for (int x = radius; x < (width - radius); x++)
        {
            double red = 0; double green = 0; double blue = 0;
            filterToPixel(pix, width, height, core, radius, x, y, filtpix);
        }
    }
    pix = filtpix;
}



/*
-> Функция ниже главная. В ней происходит чтение и поворот изображения по часовой стрелке и против соответственно.
-> А также к обоим перевернутым изображениям применяется фильтр Гаусса.
*/
int main()
{   
    bmpdata header;
    
    std::vector<unsigned char>pix;
    
    
    
    // Для поворота по часовой стрелке + фильтр Гаусса.
    
    bmpread("image.bmp", pix, header);
    
    rotateImageRight(pix, header.width, header.height);
    header.fileSize = sizeof(header) + pix.size();
    
    bmpwrite("right.bmp", pix, header);
    std::cout<<"Файл image.bmp повернут на 90 градусов вправо и загружен в файл right.bmp!"<<std::endl;
    
    filterOfGauss(pix, header.width, header.height);
    bmpwrite("rightGauss.bmp", pix, header);
    std::cout<<"Фильтр Гаусса применен!"<<std::endl;
    
    
    
    // Для поворота против часовой стрелки + фильтр Гаусса.
    
    bmpread("image.bmp", pix, header); 
 
    rotateImageLeft(pix, header.width, header.height);
    header.fileSize = sizeof(header) + pix.size();
    
    bmpwrite("left.bmp", pix, header);  
    std::cout<<"Файл image.bmp повернут на 90 градусов влево и загружен в файл left.bmp!"<<std::endl;
    
    filterOfGauss(pix, header.width, header.height);
    bmpwrite("leftGauss.bmp", pix, header);
    std::cout<<"Фильтр Гаусса применен!"<<std::endl;
    
    
    
    return 0;
}
