#include "Dialogbox.h"
#include "MainMenu.h"
Dialogbox::Dialogbox()
{

}

std::string Dialogbox::showBox(int n)
{
  OPENFILENAME ofn;
    ZeroMemory( &filename, sizeof( filename ) );
    ZeroMemory( &ofn,      sizeof( ofn ) );
    ofn.lStructSize  = sizeof( ofn );
    ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
    if (n==1)
        ofn.lpstrFilter  = "Image Files\0*.png;*.jpg;*.jpeg;*.bmp\0Any File\0*.*\0";
    else
        ofn.lpstrFilter  = "Video Files\0*.mp4;*.avi;*.flv;*.mkv;*.m4v\0";
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Open File";
   // ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

  if (GetOpenFileNameA( &ofn ))
  {
    std::cout << "You chose the file \"" << filename << "\"\n";
  }
  else
  {
    // All this stuff below is to tell you exactly how you messed up above.
    // Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
    switch (CommDlgExtendedError())
    {
      case CDERR_DIALOGFAILURE   : std::cout << "CDERR_DIALOGFAILURE\n";   break;
      case CDERR_FINDRESFAILURE  : std::cout << "CDERR_FINDRESFAILURE\n";  break;
      case CDERR_INITIALIZATION  : std::cout << "CDERR_INITIALIZATION\n";  break;
      case CDERR_LOADRESFAILURE  : std::cout << "CDERR_LOADRESFAILURE\n";  break;
      case CDERR_LOADSTRFAILURE  : std::cout << "CDERR_LOADSTRFAILURE\n";  break;
      case CDERR_LOCKRESFAILURE  : std::cout << "CDERR_LOCKRESFAILURE\n";  break;
      case CDERR_MEMALLOCFAILURE : std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
      case CDERR_MEMLOCKFAILURE  : std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
      case CDERR_NOHINSTANCE     : std::cout << "CDERR_NOHINSTANCE\n";     break;
      case CDERR_NOHOOK          : std::cout << "CDERR_NOHOOK\n";          break;
      case CDERR_NOTEMPLATE      : std::cout << "CDERR_NOTEMPLATE\n";      break;
      case CDERR_STRUCTSIZE      : std::cout << "CDERR_STRUCTSIZE\n";      break;
      case FNERR_BUFFERTOOSMALL  : std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
      case FNERR_INVALIDFILENAME : std::cout << "FNERR_INVALIDFILENAME\n"; break;
      case FNERR_SUBCLASSFAILURE : std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
      default                    :
          {
              std::cout << "Open: You didn't select any file.\n";
          }
    }
  }
  return filename;
}
std::string Dialogbox::showBox1()
{
    OPENFILENAME ofn;
    ZeroMemory( &filename, sizeof( filename ) );
    ZeroMemory( &ofn,      sizeof( ofn ) );
    ofn.lStructSize  = sizeof( ofn );
    ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter  = "Image Files\0*.png;*.jpg;*.jpeg;*.bmp\0Any File\0*.*\0";
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Save File";
    if (GetSaveFileNameA( &ofn ))
    {
        std::cout << "You saved the file \"" << filename << "\"\n";
    }
    else
    {
       switch (CommDlgExtendedError())
        {
          case CDERR_DIALOGFAILURE   : std::cout << "CDERR_DIALOGFAILURE\n";   break;
          case CDERR_FINDRESFAILURE  : std::cout << "CDERR_FINDRESFAILURE\n";  break;
          case CDERR_INITIALIZATION  : std::cout << "CDERR_INITIALIZATION\n";  break;
          case CDERR_LOADRESFAILURE  : std::cout << "CDERR_LOADRESFAILURE\n";  break;
          case CDERR_LOADSTRFAILURE  : std::cout << "CDERR_LOADSTRFAILURE\n";  break;
          case CDERR_LOCKRESFAILURE  : std::cout << "CDERR_LOCKRESFAILURE\n";  break;
          case CDERR_MEMALLOCFAILURE : std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
          case CDERR_MEMLOCKFAILURE  : std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
          case CDERR_NOHINSTANCE     : std::cout << "CDERR_NOHINSTANCE\n";     break;
          case CDERR_NOHOOK          : std::cout << "CDERR_NOHOOK\n";          break;
          case CDERR_NOTEMPLATE      : std::cout << "CDERR_NOTEMPLATE\n";      break;
          case CDERR_STRUCTSIZE      : std::cout << "CDERR_STRUCTSIZE\n";      break;
          case FNERR_BUFFERTOOSMALL  : std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
          case FNERR_INVALIDFILENAME : std::cout << "FNERR_INVALIDFILENAME\n"; break;
          case FNERR_SUBCLASSFAILURE : std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
          default                    : std::cout << "Save: You cancelled.\n";
        }
    }
    return filename;
}
