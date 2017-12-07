#include"detect.h"
#include <string>
#include <windows.h>
using namespace std;
using namespace cv;
//#include"stdafx.h"

tracking::tracking()
{
//    HVALUES - for orange(0,44),for red(170,180),for blue(96,158),for green(60,83)
//    SVALUES-for orange(150,291),for red(160,255),for blue(119,256),for green(66,252)
//    VVALUES -for orange(210,256),for red(60,255),for blue(81,226),for green(74,141)

    m_isTrackObjects = true;
    m_useDilate = true;
    m_useErode = true;
    m_windowName = "Object Tracking";

    m_hValues[0]    = 96;
    m_hValues[1]    = 158;
    m_sValues[0]    = 119;
    m_sValues[1]    = 256;
    m_vValues[0]    = 81;
    m_vValues[1]    = 226;
    m_framewidth    = 640;
    m_frameheight   = 480;
    m_maxobjects    = 10;
    m_minobjarea    = 360;
    m_maxobjarea    =( m_framewidth *  m_frameheight )/1.5;
}



bool tracking::Process(Mat &originalimg)
{
    m_originalImage = originalimg;
    //CONVERT ORIGINALIMAGE TO HSV
    cvtColor(m_originalImage,m_hsvImage,COLOR_BGR2HSV);
    inRange(m_hsvImage,Scalar(m_hValues[0],m_sValues[0],m_vValues[0]),Scalar(m_hValues[1],m_sValues[1],m_vValues[1]),m_binaryThreshold);

    if(m_useDilate || m_useErode )
        MorphImage(m_binaryThreshold);

    if( m_isTrackObjects)
        m_totalObjectTracked = TrackObjects(m_binaryThreshold, m_originalImage);
        return true;
}

int tracking::TrackObjects(Mat threshold, Mat& original)
{
    Mat thresholdCopy;
    threshold.copyTo(thresholdCopy);
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;
    m_coordinates.clear();
    findContours(thresholdCopy,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);

  // drawContours(original,contours,3,Scalar(0,0,255),3,8,hierarchy,0);
  //bool isObjectFound = false;
  int totalObjects = 0;
  double holdarea = 0.0;

  if((int)hierarchy.size()>0 && (int)hierarchy.size()<m_maxobjects)
  {
     //int numObjects=hierarchy.size();
     int index = 0 ;
     double area;
     while(index>=0)
     {
         Moments moment = moments((Mat)contours[index]);
         area = moment.m00;
         if(area > m_minobjarea && area < m_maxobjarea && area > holdarea )
         {
             trackingObjects c;
             c.point.x = (int)(moment.m10/area);
             c.point.y = (int)(moment.m01/area);
             c.area = area;
             m_coordinates.push_back(c);
             holdarea = area;
             circle(original,Point(c.point),20,Scalar(0,0,255),1);
             putText(original,std::to_string(c.point.x)+ "," + std::to_string(c.point.y),Point(c.point.x,c.point.y+30),1,1,Scalar(0,0,255),2);

         }
         index = hierarchy[index][0];
     }
  }
//  else
//  {
//      cout<<"Too many objects...might be noise!"<<endl;
//  }
  return  totalObjects;
}

void tracking::MorphImage(Mat& threshold)
{
    if(m_useErode)
    {
        Mat e= getStructuringElement(MORPH_ELLIPSE,Size(2,2));
        erode(threshold,threshold,e);
        erode(threshold,threshold,e);
    }
    if(m_useDilate)
    {
        Mat d=getStructuringElement(MORPH_ELLIPSE,Size(6,6));
        dilate(threshold,threshold,d);
        dilate(threshold,threshold,d);
    }
}
void on_trackbar(int n, void* a)
 {

 }

void tracking::InitTrackbars(string windowName)
{
    createTrackbar("H_MIN", windowName,&m_hValues[0],m_hValues[1],on_trackbar);
    createTrackbar("H_MAX", windowName,&m_hValues[1],m_hValues[1],on_trackbar);
    createTrackbar("S_MIN", windowName,&m_sValues[0],m_sValues[1],on_trackbar);
    createTrackbar("S_MAX", windowName,&m_sValues[1],m_sValues[1],on_trackbar);
    createTrackbar("V_MIN", windowName,&m_vValues[0],m_vValues[1],on_trackbar);
    createTrackbar("V_MAX", windowName,&m_vValues[1],m_vValues[1],on_trackbar);
}


void tracking::launch()
{
    namedWindow("Trackbars");
    InitTrackbars("Trackbars");
    namedWindow(m_windowName, CV_WINDOW_AUTOSIZE);
    Mat frame;
    VideoCapture capture(0);

    while(1)
    {

     capture.read(frame);
     flip(frame, frame, 1);
     Process(frame);
     //Mat
     imshow("THRESHOLD IMAGE.window", getBinaryThreshold());
     imshow(m_windowName, getOriginalImage());
    // imshow("HSV IMAGE.window", tracker.getHSVImage());

     //DELAY 30ms SO THAT THE SCREEN CAN REFRESH
     //IMAGE WONT APPEAR WITHOUT THE WAITKEY COMMAND
     HWND *handle = (HWND*)cvGetWindowHandle(m_windowName.c_str());
     if(waitKey(30) == 27)
     {
        destroyAllWindows();
        break;
     }
     HWND *handleTest = (HWND*)cvGetWindowHandle(m_windowName.c_str());
     if(handle != handleTest)
        break;
    }
}
