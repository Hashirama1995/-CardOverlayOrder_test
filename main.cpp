#include "Image.h"
#include "functions.h"
#include <stdlib.h>

#define P420 1.5
const double IMAGE_CONVERTION = P420;     // SET IMAGE CONVERSATION
const uint8_t firstPictureInclusion = 30;   //  FIRST FRAME OVERLAY PICTURE
const uint8_t lastPictureInclusion = 80;   // LAST FRAME OVERLAY PICTURE


int main(int argc, const char *argv[])
{   
    if(argc < 6)
    {
        std::cout<<std::endl <<"ERROR: Invalid arguments for main function" << std::endl << std::endl;
        std::cout<<"You must enter: \"..PATH\\testProject.exe\" \"..PATH/picture name\" \"..PATH/video name\" videoWidth videoHeight numberOfFramesInVideo " << std::endl<< std::endl;
        std::cout<<"Example: .\\testProject.exe \"bike2.bmp\" \"video.yuv\" 352 288 150" << std::endl<< std::endl;
        return 1;
    }   

    Image testImage(argv[1]);
    //Image testImage("bike2.bmp");

   
    testImage.transformRGBinYUV420("resultPicture.yuv");

    int  imgWidth, imgHeight, videoWidth, videoHeight, videoCountFrame;
    std::tie(imgWidth,imgHeight) = testImage.getSize();
    std::cout<<"image Width : "<< imgWidth <<std::endl;
    std::cout<<"image Height : "<< imgHeight <<std::endl<<std::endl;


    videoWidth = atoi(argv[3]);
    videoHeight = atoi(argv[4]);
    std::cout<<"video Width : "<< videoWidth <<std::endl;
    std::cout<<"video Height : "<< videoHeight <<std::endl<<std::endl;

    videoCountFrame = atoi(argv[5]);
    std::cout<<"Count video frame : "<< videoCountFrame <<std::endl<<std::endl;


    //unsigned long videoFrameSize = 352 * 288* IMAGE_CONVERTION;
    unsigned long videoFrameSize = videoWidth * videoHeight* IMAGE_CONVERTION;

    // IO files
    std::ifstream in_file(argv[2], std::ios::in | std::ios::binary);
   // std::ifstream in_file("video.yuv", std::ios::in | std::ios::binary);
    std::ofstream out_file("resultVideo.yuv", std::ios::out | std::ios::binary);

    unsigned char *overlaidFrame = new unsigned char[(int)videoFrameSize];
    
    // read/write image buffer one by one
    for (int i = 0; i < videoCountFrame; i++)
    { 
        if(i > firstPictureInclusion && i < lastPictureInclusion)
        {
            out_file.write(reinterpret_cast<char *>(
                addPictureOnFrame(overlaidFrame, testImage.getYUVBuffer(), videoWidth, videoHeight, imgWidth, imgHeight)), videoFrameSize
                );
            //out_file.write(reinterpret_cast<char *>(addPictureOnFrame(overlaidFrame, testImage.getYUVBuffer(), 352, 288, imgWidth, imgHeight)), videoFrameSize);
            in_file.seekg((i+1) * videoFrameSize); 
            continue;
        }
        in_file.read(reinterpret_cast<char*>(overlaidFrame), videoFrameSize);
        out_file.write(reinterpret_cast<char *>(overlaidFrame), videoFrameSize);
    }

    std::cout << "THE PICTURE HAS BEEN OVERLAID" << std::endl<< std::endl << std::endl;

    out_file.close();
    in_file.close();
    delete [] overlaidFrame;
    return 0;
}