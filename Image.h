#pragma once
#include <vector>

class Image
{
public:
    Image(const char*);
    ~Image();

    std::tuple<int,int> getSize();
    unsigned char* getRGBBuffer();
    unsigned char* getYUVBuffer();
    
    void importBM(const char* path);
    void transformRGBinYUV420(const char* path);

private:
    int m_width;
    int m_heigth;

    unsigned char* imgbuffer;
    unsigned char* imgbuffer2;   

};