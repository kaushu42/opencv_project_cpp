#ifndef OBJECT_H
#define OBJECT_H
#include<iostream>
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/core/core.hpp"
#include<string>

struct trackingObjects
{
    CvPoint point;
    double area;
};
class tracking
{
public:
    tracking();
    bool Process(cv::Mat &originalimg);
    void InitTrackbars(std::string windowName);

    std::string intToString(int number);

    void setframewidth(int framewidth)
    {
        m_framewidth= framewidth;
    }
    void setframeheight(int frameheight)
    {
        m_frameheight= frameheight;
    }
    void setmaxobjects(int maxobjects)
    {
        m_maxobjects= maxobjects;
    }
    void setmaxobjarea(int maxobjarea)
    {
        m_maxobjarea= maxobjarea;
    }
    void setminobjarea(int minobjarea)
    {
        m_minobjarea=minobjarea;
    }

    void setShowTrackbar(bool isshow)
    {
        m_showTrackbar= isshow;
    }
    void setUseErode(bool useErode)
    {
        m_useErode= useErode;
    }
    void setUseDilate(bool useDilate)
    {
        m_useDilate= useDilate;
    }
    void setIsTrackObjects(bool isTrackable)
    {
        m_isTrackObjects= isTrackable;
    }
    int getframewidth(){return m_framewidth;}
    int getframeheight(){return m_frameheight;}
    int getmaxobjects(){ return m_maxobjects;}
    int getmaxobjarea(){return m_maxobjarea;}
    int getminobjarea(){return m_minobjarea;}

    int setShowTrackbar(){return m_showTrackbar;}
    int setUseErode(){return m_useErode;}
    int setUseDilate(){return m_useDilate;}
    int setIsTrackObjects(){return m_isTrackObjects;}

    std::vector<trackingObjects> gettrackingCoordinates()
    {
        if(m_isTrackObjects)
            return m_coordinates;

        return std::vector<trackingObjects>();
    }
    int getTotalObjectTracked()
    {
        if(m_isTrackObjects)
            return m_totalObjectTracked;
        return 0;
    }
    cv::Mat getOriginalImage(){return m_originalImage;}
    cv::Mat getHSVImage(){return m_hsvImage;}
    cv::Mat getBinaryThreshold(){
        //cv::flip(m_binaryThreshold, m_binaryThreshold, 1);
        return m_binaryThreshold;
        }
    int* getHueValues(){return m_hValues;}
    int* getSaturatedValues(){return m_sValues;}
    int* getValueValues(){return m_vValues;}
    void launch();

private:
    bool m_showTrackbar;
    bool m_useErode;
    bool m_useDilate;
    bool m_isTrackObjects;

    int m_framewidth;
    int m_frameheight;
    int m_maxobjects;
    int m_maxobjarea;
    int m_minobjarea;
    int m_totalObjectTracked;

    int m_hValues[2];
    int m_sValues[2];
    int m_vValues[2];

    cv::Mat m_originalImage;
    cv::Mat m_hsvImage;
    cv::Mat m_binaryThreshold;

    std::string m_windowName;
    std::vector<trackingObjects>m_coordinates;
    void MorphImage(cv::Mat&);
    int TrackObjects(cv::Mat,cv::Mat&);

};
#endif // OBJECT_H

