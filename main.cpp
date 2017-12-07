#include "MainMenu.h"
using namespace cv;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR l1, int n)
{
    MainMenu mainMenu;
    mainMenu.showMenu();
    cv::waitKey();
    mainMenu.launch();
    return 0;
}
