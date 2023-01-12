#include <UI/MainFrame.hpp>

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/dcbuffer.h>
#include <wx/image.h>
#include <wx/wx.h>

class MyApp : public wxApp {
  public:
    bool OnInit() {
        MainFrame *frame = new MainFrame("Speed Gun");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
