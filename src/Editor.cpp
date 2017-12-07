#include "Editor.h"
#include "MainMenu.h"
using namespace cv;
Editor* Editor::ptr = new Editor();
std::string Editor::_mainWindow = "Editor";


Mat Editor::_mainImage = Mat(1,1, CV_64F, cvScalar(0.));
Mat Editor::_filterImage = Mat(1,1, CV_64F, cvScalar(0.));
Mat Editor::_original = Mat(1,1, CV_64F, cvScalar(0.));
Mat Editor::_temp = Mat(1,1, CV_64F, cvScalar(0.));
Editor::Editor():_filterFilePath(MainMenu::ExePath() + "/" + "filter.png"),bSlider(50),cSlider(50)
{
    _filterWindow = "Filters";
}

void Editor::open()
{
      destroyAllWindows();
     //namedWindow(_mainWindow, WINDOW_NORMAL);
     _filterImage = imread(_filterFilePath, 1);

     _mainFilePath = Dialogbox::showBox(1);

    if(_mainFilePath == "")
    {
        MessageBox(NULL, "No Image Selected.", "Error", MB_OK | MB_ICONERROR);
        returnToMain();
    }

    _mainImage = imread(_mainFilePath, 1 );
    _original = imread(_mainFilePath, 1 );
    _temp = imread(_mainFilePath, 1 );

    if(_mainImage.empty())
    {
        printf( "No image data in _mainImage.\n");
        exit(1);
    }
    namedWindow(_mainWindow, WINDOW_FREERATIO);
    imshow(_mainWindow, _mainImage);

    std::cout<<std::endl<< _mainFilePath <<std::endl;

    waitKey(0);
    selectFilter();
}
void Editor::selectFilter()
{
    if(_filterImage.empty())
    {
        printf("No image data in _filterImage. Please check the file: %s\n", _filterFilePath.c_str());
        exit(1);
    }
    showMenu();
}

void Editor::showMenu()
{
    //Due to the setMouseCallback function, the program still checks for events even though it is not in a infinite loop checking for events
    //So, all mouse events are processed by the window until a key is pressed
    imshow(_filterWindow, _filterImage);
    setMouseCallback(_filterWindow, mCallback);
    waitKey();
}

void Editor::mCallback(int event, int x, int y, int , void* userdata)
{
    if((x >= 50 && x <= 220 && y >=125 && y<=170)) //START AND END COORDINATES OF CAMERA BUTTON
    {
        if(event == EVENT_LBUTTONDOWN) //IF THE LEFT MOUSE BUTTON IS PRESSED
            {
                Mat temp = _mainImage.clone();
                bitwise_not(temp, _mainImage);

                imshow(_mainWindow, _mainImage);
            }
    }
   else if(x >= 50 && x <= 220 && y >= 200 && y <=245)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                    Mat kernel = (Mat_<float>(3,3) << 1.0/2.0, 0.5/2.0, 0.9/2.0,
                                                      0.4/2.0, 0.8/2.0, 0.7/2.0,
                                                      0.9/2.0, 0.8/2.0, 0.7/2.0);

                    Mat temp = _mainImage.clone();
                    transform(temp, _mainImage, kernel);
                    imshow(_mainWindow, _mainImage);
            }
    }
    else if(x >= 50 && x <= 220 && y >= 275 && y <=322)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                    Mat kernel = (Mat_<float>(3,3) << 0.272, 0.534, 0.131,
                                                      0.349, 0.686, 0.168,
                                                      0.393, 0.769, 0.189);

                    Mat temp = _mainImage.clone();
                    transform(temp, _mainImage, kernel);
                    imshow(_mainWindow, _mainImage);
            }
    }
    else if(x >= 50 && x <= 220 && y >= 350 && y <=395)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                    Mat kernel = (Mat_<float>(3,3) << 0.503, 0.1202, 0.7111,
                                                      0.522, 0.3510, 0.4168,
                                                      0.593, 0.8, 1);

                    Mat temp = _mainImage.clone();
                    transform(temp, _mainImage, kernel);
                    imshow(_mainWindow, _mainImage);
            }
    }
    else if(x >= 50 && x <= 220 && y >= 425 && y <=470)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                    Mat kernel = (Mat_<float>(3,3) << 0.303, 0.202, 0.111,
                                                      0.222, 0.510, 0.168,
                                                      0.393, 0.248, 0.81);

                    Mat temp = _mainImage.clone();
                    transform(temp, _mainImage, kernel);
                    imshow(_mainWindow, _mainImage);
            }
    }
    else if(x >= 50 && x <= 220 && y >=500  && y <=545)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                    Mat kernel = (Mat_<float>(3,3) << 0.6, 0.2, 0.6,
                                                      0.8, 0.5, 0.8,
                                                      0.4, 0.2, 0.4);

                    Mat temp = _mainImage.clone();
                    transform(temp, _mainImage, kernel);
                    imshow(_mainWindow, _mainImage);
            }
    }
    else if(x >= 250 && x <= 420 && y >= 125 && y <=170)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                    Mat kernel = (Mat_<float>(3,3) <<   1/3.0, 1/3.0, 1/3.0,
                                                        1/3.0, 1/3.0, 1/3.0,
                                                        1/3.0, 1/3.0, 1/3.0);

                    Mat temp = _mainImage.clone();
                    transform(temp, _mainImage, kernel);
                    imshow(_mainWindow, _mainImage);
            }
    }
    else if(x >= 250 && x <= 420 && y >= 500 && y <= 545)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                const int result = MessageBox(NULL,"Select another file?", "Ask",MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2);
                switch(result)
                {
                    case IDOK:
                        ptr->Editor::open();
                    case IDCANCEL:
                        break;
                }

            }
    }
    else if(x >= 250 && x <= 420 && y >= 275 && y <=322)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                _temp = _mainImage.clone();
                ptr->Editor::makeSliders();
            }
    }
    else if(x >= 250 && x <= 420 && y >= 425 && y <=470)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                ptr->Editor::saveImage();
            }
    }
    else if(x >= 417 && x <= 456 && y >= 545 && y <= 586)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                const int result = MessageBox(NULL,"Do you want to quit?", "Exit", MB_ICONERROR | MB_YESNO | MB_DEFBUTTON2);
                switch(result)
                {
                    case IDYES:
                        ptr->Editor::returnToMain();
                    case IDCANCEL:
                        break;
                }
            }
    }
    else if(x >= 250 && x<= 420 && y>= 200 && y<= 245)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                    Mat kernel = (Mat_<float>(3,3) <<   1/7.0, 1/7.0, 1/7.0,
                                                        1/7.0, 1/7.0, 1/7.0,
                                                        1/7.0, 1/7.0, 1/7.0);

                    Mat temp = _mainImage.clone();
                    transform(temp, _mainImage, kernel);
                    imshow(_mainWindow, _mainImage);
            }
    }
    else if(x >= 250 && x<= 420 && y>= 350 && y<= 395)
    {
        if(event == EVENT_LBUTTONDOWN)
            {
                _mainImage = _original.clone();
                imshow(_mainWindow, _mainImage);
            }
    }
}

void Editor::makeSliders()
{
    destroyWindow(_filterWindow);
    createTrackbar("Brightness", _mainWindow, &bSlider, 100, bCallback, &cSlider); //Creating trackbars
    createTrackbar("Contrast", _mainWindow, &cSlider, 100, cCallback, &bSlider);
    waitKey();
    showMenu();
}

void Editor::bCallback(int brightness, void* contrast)
{
    double bVal = brightness - 50.0;
    double cVal = *(static_cast<int*>(contrast)) / 50.0;
    Mat temp;
    _temp.convertTo(temp, -1, cVal, bVal);
    imshow(_mainWindow, temp);
    _mainImage = temp;
}

void Editor::cCallback(int contrast, void* brightness)
{
    double bVal = *(static_cast<int*>(brightness)) - 50.0;
    double cVal = (contrast) / 50.0;
    Mat temp;
    _temp.convertTo(temp, -1, cVal, bVal);
    imshow(_mainWindow, temp);
    _mainImage = temp;
}

void Editor::saveImage()
{
    _saveFilePath = Dialogbox::showBox1();
    if (_saveFilePath == "")
    {
        Editor::showMenu();
    }
    imwrite(_saveFilePath + ".jpg", _mainImage);
    returnToMain();
}

void Editor::returnToMain()
{
    MainMenu::setUserChoice(NO_CHOICE);
    destroyAllWindows();
    MainMenu::showMenu();
    MainMenu::launch();
}
