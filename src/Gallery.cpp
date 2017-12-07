#include "Gallery.h"
#include "MainMenu.h"
Gallery::Gallery()
{

}

void Gallery::launch()
{
    _filePath = Dialogbox::showBox(2);
    cv::destroyAllWindows();
    if(_filePath == "")
    {
        MessageBox(NULL, "No Video Selected.", "Error", MB_OK | MB_ICONERROR);
        MainMenu::setUserChoice(NO_CHOICE);
        MainMenu::showMenu();
        MainMenu::launch();
        return;
    }
    std::string temp1 = "\"" ;
    std::string temp2 = temp1 +  _filePath + temp1;
    system(temp2.c_str());
    cv::destroyAllWindows();
    MainMenu::showMenu();
    MainMenu::launch();
    //system("pause");
}
