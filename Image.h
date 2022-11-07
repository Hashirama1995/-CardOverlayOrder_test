#pragma once
#include <iostream>
#include <fstream>
#include <tuple>
#include <thread>

class Image
{
public:
    Image(const char*);
    ~Image();

    std::tuple<int,int> getSize();
    unsigned long getImagePixelSize();
    unsigned char* getRGBBuffer();
    unsigned char* getYUVBuffer();
    
    void importBM(const char* path);
    void transformRGBinYUV420(const char* path);

private:
    int m_width;
    int m_heigth;
    unsigned long image_pixel_size;

    unsigned char* imgbufferRGB;
    unsigned char* imgbufferYUV;   
};