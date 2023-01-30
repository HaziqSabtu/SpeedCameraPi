#include <UI/MainFrame.hpp>

#include <Utils/Logger.hpp>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/dcbuffer.h>
#include <wx/image.h>
#include <wx/log.h>
#include <wx/wx.h>

class MyApp : public wxApp {
  public:
    bool OnInit() {
        // wxLog *logger = new Logger();
        wxLog::SetActiveTarget(new AppLogger);
        wxLogMessage("Application Started");
        MainFrame *frame = new MainFrame("Speed Gun");
        frame->Show(true);
        return true;
    }

    virtual int OnExit() {
        wxLogMessage("Application Closed");
        return wxApp::OnExit();
    }
};

wxIMPLEMENT_APP(MyApp);
