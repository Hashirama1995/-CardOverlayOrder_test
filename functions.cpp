#include <fstream>
#include <iostream>
#include "functions.h"
#include <vector>
#include <algorithm>



unsigned char* addPictureOnFrame (unsigned char* frame, unsigned char* picture, int frameSize, int picSize)
{
    unsigned char *resultFrame = new unsigned char [frameSize * 1.5];
    if(frameSize >= picSize)
    {    
        unsigned char *Y_frame = new unsigned char [frameSize];
        unsigned char *U_frame = new unsigned char [frameSize/4];
        unsigned char *V_frame = new unsigned char [frameSize/4];

        unsigned char *Y_pic = new unsigned char [picSize];
        unsigned char *U_pic = new unsigned char [picSize/4];
        unsigned char *V_pic = new unsigned char [picSize/4];

        if(frameSize == picSize)
        {
            int count_byte = 0;
            for(int i = 0; i < frameSize; i++)
            {   
                Y_frame[i] = frame[count_byte];
                Y_pic[i] = picture[count_byte];
                Y_frame[i] = Y_pic[i];
                count_byte++;
            }
            for(int i = 0; i < frameSize/4; i++)
            {
                U_frame[i] = frame[count_byte];
                U_pic[i] = picture[count_byte];
                U_frame[i] = U_pic[i];
                count_byte++;
            }
            for(int i = 0; i < frameSize/4; i++)
            {
                V_frame[i] = frame[count_byte];
                V_pic[i] = picture[count_byte];
                V_frame[i] = V_pic[i];
                count_byte++;
            }      
        
            count_byte = 0;
            for(int i = 0; i < frameSize; i++)
            {   
                resultFrame[count_byte] = Y_frame[i];
                count_byte++;
            }
                for(int i = 0; i < frameSize/4; i++)
            {
                resultFrame[count_byte] = U_frame[i];
                count_byte++;
            }
            for(int i = 0; i < frameSize/4; i++)
            {
                resultFrame[count_byte] = V_frame[i];
                count_byte++;
            }
            delete[] Y_frame;
            delete[] U_frame;
            delete[] V_frame;

            delete[] Y_pic;
            delete[] U_pic;
            delete[] V_pic;         
        }
    }   
    return resultFrame;
}