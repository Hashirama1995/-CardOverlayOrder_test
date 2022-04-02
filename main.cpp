#include "Image.h"
#include "functions.h"
#include <tuple>
#include <fstream>
#include <iostream>

#define P420 1.5

const int IMAGE_SIZE = 352*288;             //SET IMAGE SIZE 
const double IMAGE_CONVERTION = P420;       // SET IMAGE CONVERSATION
const uint8_t n_frames = 150;               // SET NUMBERS OF FRAME IN VIDEO
const uint8_t firstPictureInclusion = 30;   //  FIRST FRAME OVERLAY PICTURE
const uint8_t lastPictureInclusion = 100;   // LAST FRAME OVERLAY PICTURE

void main (int argc, const char* args[])
{
    Image copyImage("bike2.bmp");
    copyImage.transformRGBinYUV420("resultPicture.yuv");

    double image_size = IMAGE_SIZE * IMAGE_CONVERTION;
    long file_size = 0;

    // IO files
    std::ifstream in_file("video.yuv", std::ios::in | std::ios::binary);
    std::ofstream out_file("resultVideo.yuv", std::ios::out | std::ios::binary);

    unsigned char* image = new unsigned char[(int)image_size];

    // read/write image buffer one by one
    
        
        for(int i = 0; i < n_frames; i++)
        {
            in_file.read(reinterpret_cast<char*>(image), image_size);             
        
            if(i > firstPictureInclusion && i < lastPictureInclusion)
            {
                out_file.write(reinterpret_cast<char*>(addPictureOnFrame(image,copyImage.getYUVBuffer(),IMAGE_SIZE,IMAGE_SIZE)), image_size);
                continue;
            }

            out_file.write(reinterpret_cast<char*>(image), image_size);
        }
    
    std::cout<<"THE PICTURE HAS BEEN OVERLAID"<<std::endl;

    out_file.close();
    in_file.close();

    std::cout<<"END THE PROGRAMM"<<std::endl; 
}