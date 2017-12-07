#ifndef EDITOR_H
#define EDITOR_H
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <dialogbox.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

class Editor : public Dialogbox
{
    public:
        std::string _filterFilePath;
        Editor();
        void open();
        static void mCallback(int event, int x, int y, int , void* userdata);
        void makeSliders();
        void saveImage();
        void returnToMain();


    protected:

    private:
        static cv::Mat _mainImage;
        static cv::Mat _original;
        static cv::Mat _temp;
        static cv::Mat _filterImage;
        static std::string _mainWindow;
        std::string _filterWindow;
        std::string _mainFilePath;
        std::string _saveFilePath;
        void showMenu();
        void selectFilter();
        int bSlider, cSlider;
        static void bCallback(int brightness, void* contrast);
        static void cCallback(int contrast, void* brightness);
        static Editor* ptr;
};

#endif // EDITOR_H
