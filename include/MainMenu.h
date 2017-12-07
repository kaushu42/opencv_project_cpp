#ifndef MAINMENU_H
#define MAINMENU_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
enum CHOICE{NO_CHOICE = 0, CAMERA, EDITOR, FACE, OBJECT, GALLERY};
class MainMenu
{
    public:
        MainMenu();

        static  void launch();

        static std::string ExePath();
        static std::string mainDirectory;

        static void showMenu();
        static void mCallback(int event, int x, int y, int flags, void* userdata);
        static void setUserChoice(int n);

    protected:

    private:
        static cv::Mat menuImage;

        static std::string _windowName;
        static std::string _fileName;

        static int _userChoice;


};

#endif // MAINMENU_H

