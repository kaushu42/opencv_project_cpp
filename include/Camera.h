#ifndef CAMERA_H
#define CAMERA_H
#define DIRNAME "C:\\Snaps"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <dir.h>

class Camera
{
    public:
        Camera();
        void launch();

    protected:

    private:
        static void mCallback(int event, int x, int y, int flags, void* userdata);
        std::string _fileName;
        cv::VideoCapture _cap;
        cv::Mat _cameraImage;
        cv::Mat _imageWithCamera;
        void createCameraButtonImage();
        static std::string _windowName;
        static int _height;
        static int _width;
        static void capture(void* data);
};

#endif // CAMERA_H
