#include "Image.h"


//static int image_pixel_size;

Image::Image(const char* path)
{
    //OPEN STREAM
    std::fstream f;
    f.open(path,std::ios::in | std::ios::binary);
    if(!f.is_open())
    {
        std::cout<<"File is not open2"<<std::endl;
        f.close();
        exit(0);
    }

    //DECLARATION VAR
    const int fileHeaderSize = 14; 
    const int informationHeaderSize = 40; 
    int fileSize;
    int start_pos;

    //READ HEADER,INITIALIZE VAR
    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader),fileHeaderSize);
    if(fileHeader[0] !='B' || fileHeader[1] != 'M')
    {
        std::cout<<"Error, is it not Bitmap image"<<std::endl;
        f.close();
        exit(0);
    }    
 
    //READ INFO,INITIALIZE VAR
    unsigned char informationHeader[informationHeaderSize];
    f.read(reinterpret_cast<char*>(informationHeader),informationHeaderSize);

    fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_heigth = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);
    start_pos = fileHeader[10];

    image_pixel_size = m_width * m_heigth;
    imgbufferRGB = new unsigned char[image_pixel_size*3];

    //READ R_B_G
    f.clear();
    f.seekg(start_pos);
    f.read(reinterpret_cast<char*>(imgbufferRGB), (image_pixel_size)*3); 
    f.close();
}

Image::~Image()
{    
    delete[] imgbufferRGB;
    delete[] imgbufferYUV;
}

std::tuple<int,int> Image::getSize() 
{
    return std::tuple<int, int>(m_width,m_heigth);
}

unsigned long Image::getImagePixelSize()
{
    return image_pixel_size;
}

unsigned char* Image::getRGBBuffer()
{
    return imgbufferRGB;
}

unsigned char* Image::getYUVBuffer()
{
    return imgbufferYUV;
}

void Image::transformRGBinYUV420(const char* path)
{
    size_t image_size = m_width * m_heigth;
       
    size_t vpos = image_pixel_size/4-1;             //AFTER RGB->YUV420 IMAGE WILL BE UPSIDE DOWN
    size_t upos = image_pixel_size/4-1;             // WE MUST FILL AN ARRAY IN REVERSE
    size_t ypos = image_pixel_size-1;

    imgbufferYUV = new unsigned char [image_pixel_size * 1.5];
    unsigned char* Y = new unsigned char [image_pixel_size];
    unsigned char* U = new unsigned char [image_pixel_size/4];
    unsigned char* V = new unsigned char [image_pixel_size/4];    
    
    std::thread t1(
        [&]() {
        size_t i = 0; 
        for( size_t line = 0; line < m_heigth; line++ )
        {
            for( size_t x = 0; x < m_width; x += 1 )//2
            {              
                uint8_t r = imgbufferRGB[3 * i];
                uint8_t g = imgbufferRGB[3 * i + 1];
                uint8_t b = imgbufferRGB[3 * i + 2];
                        
                Y[ypos--] = ((66*r + 129*g + 25*b) >> 8) + 16;
                ++i;   
            }                    
        }

        unsigned char temp;
        for(int y = 0; y < m_heigth; y++)
        {
            for(int x=0; x < m_width/2; x++)
            {
                temp = (Y[y * m_width + x]);
                Y[y * m_width + x] = Y[y * m_width + m_width -1 - x];
                Y[y * m_width + m_width - 1 - x] =temp;
            }
        }
        //std::cout<<"Thread number " <<std::this_thread::get_id() << " ended"<<std::endl; 
    });

    std::thread t2(
        [&]() {
        size_t i = 0;

        for( size_t line = 0; line < m_heigth; line+=2 ) //line++
        {
            for( size_t x = 0; x < m_width; x += 2 )
            {              
                uint8_t r = imgbufferRGB[3 * i];
                uint8_t g = imgbufferRGB[3 * i + 1];
                uint8_t b = imgbufferRGB[3 * i + 2];
                        
                ++i;
                V[upos--] = ((-38*r + -74*g + 112*b) >> 8) + 128;
                U[vpos--] = ((112*r + -94*g + -18*b) >> 8) + 128;       
                ++i;
            }

            i+=m_width;                   
        }

        unsigned char temp;
        for(int y = 0; y < m_heigth/2; y++)
        {
            for(int x = 0; x < m_width/4; x++)
            {
                temp = (U[y * m_width/2 + x]);
                U[y * m_width/2 + x]=U[y * m_width / 2 + m_width / 2 - 1 - x];
                U[y * m_width/2 + m_width / 2 -1 - x] = temp;


                temp = ( V[y * m_width/2 + x]);
                V[y * m_width/2 + x] = V[y * m_width/2 + m_width/2 - 1 - x];
                V[y * m_width/2 + m_width/2 - 1 - x] = temp;
            }
        }
        //std::cout<<"Thread number " <<std::this_thread::get_id() << " ended"<<std::endl; 
    });

    t1.join();
    t2.join();

    for(int i = 0; i < image_pixel_size; i++)
    {   
        imgbufferYUV[i] = Y[i];
    }
    for(int i = 0; i < image_pixel_size/4; i++)
    {
        imgbufferYUV[i + image_pixel_size] = U[i];
        imgbufferYUV[i + image_pixel_size + image_pixel_size/4] = V[i];
    }
    
    std::fstream f2;
    f2.open(path, std::ios::out | std::ios::binary);
    if(!f2.is_open())
    {
        std::cout<<"File is not open"<<std::endl;
        f2.close();
        exit(0);
    }

    f2.write(reinterpret_cast<char*>(imgbufferYUV), image_pixel_size*1.5);
    f2.close();
    std::cout<< std::endl <<".YUV IMAGE FILE CREATED"<<std::endl;
    delete[]Y;
    delete[]U;
    delete[]V;
}