#ifndef FACERECOG_H
#define FACERECOG_H
#include <iostream>
#include <vector>
#include <string>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


class FaceRecog
{
    public:
        FaceRecog();
        void launch();


    protected:

    private:
        cv::VideoCapture _cap;
        void convertToGray(cv::Mat& inputMat, cv::Mat& outputMat);
        void resizeImage(cv::Mat& inputMat, cv::Mat& outputMat);
        void detectFaces(cv::Mat& inputMat, int accuracy);
        void enlargeRect(cv::Mat& inputMat);
        std::vector <cv::Rect> _faces;
        const std::string _windowName;
        const std::string _cascadeFilePath;
        cv::CascadeClassifier _faceDetect;
        const int DETECTION_WIDTH;
        float _scaledWidth;

};

#endif // FACERECOG_H
