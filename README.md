# testProject
my test for elecard
The program converts .bmp image to .yuv420 and overlays .yuv video from 30 to 100 frames.

1) If you want to run the built project:
- Go to release folder via terminal
- open executable
- after launch, 2 .yuv files will be created
- resultPicture.yuv is the converted picture
- resultVideo.y4m video with overlay

2) If you want to build a project
- open sources folder in your IDE
- build the project (CMake build system)
- copy video.yuv from yav_video folder to bin/Debug/ folder
- copy bike2.bmp from bitmap_image folder to bin/Debug/ folder
ATTENTION:
The project only supports resolution (352*288) and number of frames=150

If you want to use a different resolution and frame rate, or
change the number of superimposed frames, you need to change in main.cpp
the following variables:

const int IMAGE_SIZE = 352*288; // SET VIDEO IMAGE SIZE
const double IMAGE_CONVERTION = P420; // SET IMAGE CONVERSATION
const uint8_t n_frames = 150; // SET NUMBERS OF FRAME IN VIDEO
const uint8_t firstPictureInclusion = 30; // FIRST FRAME OVERLAY PICTURE
const uint8_t lastPictureInclusion = 100; // LAST FRAME OVERLAY PICTURE

You also need to change the path to your file in streams (image and video file)

THE PICTURE SIZE CANNOT BE GREATER THAN THE FRAME SIZE IN THE VIDEO FILE.
