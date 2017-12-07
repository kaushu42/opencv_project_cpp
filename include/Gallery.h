#ifndef GALLERY_H
#define GALLERY_H
#include <iostream>
#include <windows.h>
#include <dialogbox.h>
#include "opencv2/imgproc/imgproc.hpp"

class Gallery:public Dialogbox
{
    public:
        Gallery();
        void launch();

    protected:

    private:
        std::string _filePath;
};

#endif // GALLERY_H
