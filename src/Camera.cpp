#include "Camera.h"
#include "MainMenu.h"
using namespace cv;

std::string Camera::_windowName = "";
int Camera::_height = 0;
int Camera::_width = 0;
Camera::Camera()
{
    _windowName = "Camera";
    _cap = VideoCapture(0);
    if(!_cap.isOpened())
    {
        MessageBox(NULL, "Camera Not Found", "ERROR!", MB_OK);
        exit(1);
    }
    _height = int(_cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    _width = int(_cap.get(CV_CAP_PROP_FRAME_WIDTH));
    _imageWithCamera = Mat(_height, _width, CV_8UC3, Scalar(0, 0, 0));
    _cameraImage = imread(MainMenu::ExePath() + "/" + "img2.png");
    if(_cameraImage.empty())
    {
        std::cout << "Cannot find image of camera!" << std::endl;
        exit(1);
    }
}
void Camera::launch()
    {
        destroyAllWindows();
        createCameraButtonImage();

        Mat frame;
        namedWindow(_windowName, WINDOW_NORMAL);
        setMouseCallback(_windowName, mCallback, &frame);


        while (1)
        {


            bool bSuccess = _cap.read(frame); // read a new frame from video
            Mat temp = frame.clone();
            flip(temp, frame, 1);

            if (!bSuccess) //if not success, break loop
            {
                 MessageBox(NULL,"Cannot read a frame from video stream","ERROR!",MB_OK);
                 break;
            }
            //frame += _imageWithCamera;
            imshow(_windowName, frame + _imageWithCamera); //show the frame in "MyVideo" window
            HWND* hwnd = (HWND*)cvGetWindowHandle(_windowName.c_str());

            if(waitKey(30) == 27 )
            {
                destroyAllWindows();
                break;
            }
            HWND* hwnd1 = (HWND*)cvGetWindowHandle(_windowName.c_str());
            if(hwnd!=hwnd1)
                break;
        }
        //destroyAllWindows();
        //delete this;
        //ReturnMain::callMain();
}

void Camera::capture(void* data)
{
    //std::cout << "Capture!\n";
    waitKey(10);
    Mat *frame = (Mat* )(data);
    mkdir(DIRNAME);
    std::cout<<"Image saved at C:\\Snaps"<<std::endl;
    imwrite("C:\\Snaps\\Camera" + std::to_string(time(NULL)) + ".jpg", *frame);
    *frame = *frame + Mat(frame->rows, frame->cols, CV_8UC3, Scalar(100, 100, 100));
    imshow(_windowName, *frame);
    waitKey(100);
}


void Camera::mCallback(int event, int x, int y, int flags, void* userdata)
{
    if(x >= (_width/2 - 20) && x <= (_width/2 + 20) && y >= (_height - 50) && y <= (_height - 10))
        if(event == EVENT_LBUTTONDOWN)
            capture(userdata);
}




void Camera::createCameraButtonImage()
{
    for(int i = _imageWithCamera.rows - 50, y = 0; i < _imageWithCamera.rows - 10; i++, ++y)
    {
        for(int j= _imageWithCamera.cols/2 - 20, x = 0; j < _imageWithCamera.cols/2 + 20; j++, ++x)
        {
           _imageWithCamera.data[_imageWithCamera.step[0]*i + _imageWithCamera.step[1]* j + 0] = _cameraImage.data[_cameraImage.step[0]*y + _cameraImage.step[1]* x + 0];
           _imageWithCamera.data[_imageWithCamera.step[0]*i + _imageWithCamera.step[1]* j + 1] = _cameraImage.data[_cameraImage.step[0]*y + _cameraImage.step[1]* x + 1];
           _imageWithCamera.data[_imageWithCamera.step[0]*i + _imageWithCamera.step[1]* j + 2] = _cameraImage.data[_cameraImage.step[0]*y + _cameraImage.step[1]* x + 2];
        }
    }
}
