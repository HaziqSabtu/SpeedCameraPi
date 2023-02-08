#include <UI/MainFrame.hpp>
#include <Utils/AppConfig.hpp>
#include <Utils/Logger.hpp>
#include <wx/wx.h>

class MyApp : public wxApp {
  public:
    bool OnInit() {
        AppConfig conf;

        wxLog::SetActiveTarget(new AppLogger);
        wxLogMessage("Application Started");

        wxString filename = conf.GetFileName();
        wxString dirLocation = conf.GetDirLocation();
        wxLogMessage("Loaded: %s", filename);
        wxLogMessage("Loaded: %s", dirLocation);
        MainFrame *frame =
            new MainFrame("Speed Gun", filename, dirLocation, wxSize(800, 600));

        frame->Show(true);
        return true;
    }

    virtual int OnExit() {
        wxLogMessage("Application Closed");
        return wxApp::OnExit();
    }
};

wxIMPLEMENT_APP(MyApp);
