#include "functions.h"



unsigned char* addPictureOnFrame (unsigned char* frame, unsigned char* picture, int frameWidth, int frameHeight, int picWidth, int picHeight)
{
    int frameSize = frameWidth * frameHeight;
    int count_byte = 0;
    int count_frame = 0;

    for(int i = 0; i < picHeight; i++)
    {
        for(int j = 0; j < picWidth; j++)
        {
            frame[count_frame] = picture[count_byte];
            count_byte++;
            count_frame++;
        }

        if(count_frame < frameWidth * (i+1))
        {
            count_frame = count_frame + (frameWidth * (i+1) - count_frame);
        }
    }
    
    count_frame = frameSize;

    for(int i = 0; i < picHeight/2; i++)
    {
        for(int j = 0; j < picWidth/2; j++)
        {
            frame[count_frame] = picture[count_byte];
            frame[count_frame+frameSize/4] = picture[count_byte + (picWidth*picHeight)/4];
            count_byte++;
            count_frame++;
        }

        if(count_frame <  frameSize + frameWidth/2 * (i+1))
        {
            count_frame = frameSize + frameWidth/2 * (i+1);
        }
    }
    return frame; 
}