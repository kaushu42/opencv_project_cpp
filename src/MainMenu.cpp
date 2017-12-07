#include "MainMenu.h"
#include "Camera.h"
#include "Editor.h"
#include "Gallery.h"
#include "FaceRecog.h"
#include "Detect.h"

using namespace cv;

std::string MainMenu::_windowName = "Main Menu";
std::string MainMenu::mainDirectory = ExePath();
std::string MainMenu::_fileName = MainMenu::mainDirectory + "/" + "menu.png";

int MainMenu::_userChoice = NO_CHOICE;
Mat MainMenu::menuImage = Mat(1,1, CV_64F, cvScalar(0.));

MainMenu::MainMenu()
{
    menuImage = imread(_fileName);
    namedWindow(_windowName.c_str());
    if(menuImage.empty())
    {
        MessageBox(NULL, "Cannot find image.", "ERROR", MB_OK);

        std::exit(1);
    }

}

std::string MainMenu::ExePath()
{
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}

void MainMenu::showMenu()
{
    //Due to the setMouseCallback function, the program still checks for events even though it is not in a infinite loop checking for events
    //So, all mouse events are processed by the window until a key is pressed
    imshow(_windowName.c_str(), menuImage);
    setMouseCallback(_windowName.c_str(), mCallback, &mainDirectory);
//    HWND *hwnd = (HWND*)cvGetWindowHandle(_windowName.c_str());
    if(waitKey() == 27)
        exit(1);
//    HWND *hwnd1 = (HWND*)cvGetWindowHandle(_windowName.c_str());
//    if(hwnd1 != hwnd)
//        exit(1);
}


//This function is called by the setMouseCallback function everytime a mouse moves over the window given in setMouseCallback
//All arguments are necessary and used by setMouseCallback while calling this function
//Event is the type of action that occurs eg. mouse moving over a area, left click, right click, double click, etc
//x and y are the coordinates of the mouse
//flags and userdata are not used
void MainMenu::mCallback(int event, int x, int y, int flags, void* userdata)
{
    if((x >= 97 && x <= 408 && y >=140 && y<=192)) //START AND END COORDINATES OF CAMERA BUTTON
    {
        if(event == EVENT_LBUTTONDOWN) //IF THE LEFT MOUSE BUTTON IS PRESSED
            {
               // MessageBox(NULL, "Camera", "Launch Camera", MB_OK);
                _userChoice = CAMERA;
                destroyAllWindows();
                return;
            }
    }
    else if(x >= 430 && x <= 487 && y >= 595 && y <=645) //QUIT
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                int test = MessageBox(NULL, "Are you sure you want to quit?", "Quit", MB_OKCANCEL |MB_ICONERROR | MB_DEFBUTTON2);
                if(test == IDOK)
                    exit(1);
            }
    }
    else if(x >= 34 && x <= 90 && y >= 595 && y <=645) //HELP
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                std::ifstream file;
                file.open(*((std::string*)(userdata)) + "/" + "helptext.dat");
                std::string text;
                std::string line;
                while(getline(file, line))
                    text += line + '\n';
                MessageBox(NULL, text.c_str(), "Help", MB_ICONQUESTION | MB_OK );
            }
    }
    else if(x >= 97 && x <= 408 && y >= 228 && y <=287) //EDITOR
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                //MessageBox(NULL, "This is the Editor", "Editor", MB_OK);
                _userChoice = EDITOR;
                destroyAllWindows();
                return;
            }
    }
    else if(x >= 97 && x <= 408 && y >= 322 && y <=382) //FACE DETECT
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                _userChoice = FACE;
                destroyAllWindows();
                return;
            }
    }
    else if(x >= 97 && x <= 408 && y >= 426 && y <=486) //OBJECT DETECT
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                _userChoice = OBJECT;
                destroyAllWindows();
                return;

            }
    }
        else if(x >= 100 && x <= 410 && y >= 530 && y <=590) //OBJECT DETECT
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                _userChoice = GALLERY;
                destroyAllWindows();
                return;

            }
    }
        else if(x >= 232 && x <= 288 && y >= 595 && y <=645) //OBJECT DETECT
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                MessageBox(NULL, "Graphics Studio \nVersion 1.0.0 \nDeveloped by: \n  Janardan Banjara (072/BEX/419)\n  Karuna Karki (072/BEX/421)\n  Kaushal Raj Mishra (072/BEX/422)", "About", MB_ICONINFORMATION | MB_OK);
            }
    }
}

void MainMenu::launch()
{
    //setMouseCallback(_windowName, NULL);
    switch(_userChoice)
    {
        case CAMERA:
            {
                Camera *c = new Camera();
                c->launch();
                delete c;
                _userChoice = NO_CHOICE;
                showMenu();
                launch();
                break;
            }
        case EDITOR:
            {
                Editor *e = new Editor();
                e->open();
                delete e;
                _userChoice = NO_CHOICE;
                break;
            }
        case FACE:
            {
                FaceRecog *f = new FaceRecog();
                f->launch();
                delete f;
                _userChoice = NO_CHOICE;
                showMenu();
                launch();
                break;
            }
        case OBJECT:
            {
                tracking *t = new tracking();
                t->launch();
                delete t;
                destroyAllWindows();
                _userChoice = NO_CHOICE;
                showMenu();
                launch();
                break;
            }
        case GALLERY:
            {
                Gallery *g = new Gallery();
                destroyAllWindows();
                g->launch();
                delete g;
                break;
            }

    }
}

void MainMenu::setUserChoice(int n)
{
    _userChoice = n;
}

