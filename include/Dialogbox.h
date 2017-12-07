#ifndef DIALOGBOX_H
#define DIALOGBOX_H
#include <iostream>
#include <windows.h>

class Dialogbox
{
    public:
        char filename[ MAX_PATH ];
        Dialogbox();
        std::string showBox(int n);
        std::string showBox1();
    protected:

    private:
};

#endif // DIALOGBOX_H
