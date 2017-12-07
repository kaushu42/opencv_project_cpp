#include "FaceRecog.h"
#include "MainMenu.h"
#include <ctime>
using namespace cv;
FaceRecog::FaceRecog():_windowName("Face Recognition"), _cascadeFilePath(MainMenu::ExePath() + "/" + "haarcascade_frontalface_alt.xml"), DETECTION_WIDTH(320)
{
    if(!_faceDetect.load(_cascadeFilePath))
    {
        std::cout << "Cannot load the cascade classifier: " << _cascadeFilePath << std::endl;
        exit(1);
    }
    _cap.open(0);
    if(!_cap.isOpened())
    {
        std::cout << "Cannot initialize the camera." << std::endl;
    }
}

void FaceRecog::convertToGray(Mat &inputMat, Mat& outputMat)
{
	if(inputMat.channels() == 3)
		cvtColor(inputMat, outputMat, CV_BGR2GRAY);
	else if(inputMat.channels() == 4)
		cvtColor(inputMat, outputMat, CV_BGRA2GRAY);
	else outputMat = inputMat;
}

void FaceRecog::resizeImage(Mat& inputMat, Mat& outputMat)
{
	//Resize the image if the size of the image is bigger than the threshold width
	if(inputMat.cols > DETECTION_WIDTH)
	{
		_scaledWidth = inputMat.cols / static_cast<float>(DETECTION_WIDTH); //Scale to maintain the aspect ratio
		int scaledHeight = cvRound(inputMat.rows / _scaledWidth);
		resize(inputMat, outputMat, Size(DETECTION_WIDTH, scaledHeight));
	}
	else outputMat = inputMat;
}

void FaceRecog::detectFaces(Mat& inputMat, int accuracy)
{
	//faces is a vector of cv::Rect
	//1.1f is for how often faces to search. If it was 1.2f, it would be faster but doesnt find face as often
	//4 is for how sure should the detector be that a face has been found. Higher value = reliable faces
	//flags like CASCADE_SCALE_IMAGE determine how face should be found
		//CASCADE_FIND_BIGGEST_OBJECT looks for largest face only and runs faster
		//CASCADE_DO_ROUGH_SEARCH and CASCADE_SCALE_IMAGE makes the search a little faster
	//The size parameter is for how big faces the detector should detect
	_faceDetect.detectMultiScale(inputMat, _faces, 1.1f, accuracy, CASCADE_SCALE_IMAGE, Size(10, 10));
}

void FaceRecog::launch()
{
    while(1)
    {
        Mat frame;
        _cap.read(frame);
        Mat gray;
        Mat currentFrame = frame.clone();
        //First resize the image to a smaller size for faster operation
        resizeImage(currentFrame, frame); //---->Now frame contains the smaller image

        //Now convert the image to a grayscale format
        convertToGray(frame, gray); //--->Now gray contains smaller grayscale image

        //Now equalize the histogram to clear out the noise
        equalizeHist(gray, frame); //---->Now need to detect face in frame

        flip(frame, frame, 1);
        detectFaces(frame, 4);
        flip(currentFrame, currentFrame, 1);
        enlargeRect(currentFrame);
        for(unsigned int i = 0; i < _faces.size(); ++i)
        {
            putText(currentFrame, "Face Detected!", Point(_faces[i].x, _faces[i].y), FONT_HERSHEY_PLAIN, 1.2f, Scalar(255, 255, 255));
            rectangle(currentFrame, _faces[i], Scalar(0, 0, 200), 2);
        }
        imshow(_windowName.c_str(), currentFrame);
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
}
void FaceRecog::enlargeRect(Mat& inputMat)
{
    //To show the rectangle in the original image, we must resize the detected cv::Rect
    if(inputMat.cols > _scaledWidth)
    {
        for(unsigned int i = 0; i < _faces.size(); ++i)
        {
            _faces[i].x = cvRound(_faces[i].x * _scaledWidth);
            _faces[i].y = cvRound(_faces[i].y * _scaledWidth);
            _faces[i].width = cvRound(_faces[i].width * _scaledWidth);
            _faces[i].height = cvRound(_faces[i].height * _scaledWidth);
        }
    }
    //If the image is on the border of the image, keep it inside the image
    for(unsigned int i = 0; i < _faces.size(); i++)
    {
        if(_faces[i].x < 0)
            _faces[i].x = 0;
        if(_faces[i].y < 0)
            _faces[i].y = 0;
        if(_faces[i].x + _faces[i].width > inputMat.cols)
            _faces[i].x = inputMat.cols - _faces[i].width;
        if(_faces[i].y + _faces[i].height > inputMat.rows)
            _faces[i].y = inputMat.rows - _faces[i].height;

    }
}
