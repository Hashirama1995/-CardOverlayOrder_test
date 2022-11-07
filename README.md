# testProject
The program converts .bmp image to .yuv420 and overlays .yuv on video from 30 to 80 frames.

The project is built using CMake.
Additional libraries are not used.
There is a .bmp file and a .jav video file in the Resources folder.
After the project is built, you need to copy these files to the folder - .

Picture used as an example:
size - width 352, height 288.

Video used as an example:
size - width 352, height 288
Number of frames - 150.

HOW TO START A PROJECT?
        You must enter: ..PATH\testProject.exe "..PATH/picture name" "..PATH/video name" videoWidth videoHeight numberOfFramesInVideo 

To run the example (if you have previously copied the picture and video to the .exe folder)
        Example: .\testProject.exe "bike2.bmp" "video.yuv" 352 288 150

If you want to use a different video and picture, you need to specify as parameters when starting .exe:
        image path, video path, video width, video height, number of frames in the video.
