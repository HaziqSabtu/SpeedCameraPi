#include <UI/Frame/MainFrame.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Logger/Logger.hpp>
#include <wx/thread.h>
#include <wx/utils.h>
#include <wx/wx.h>

class MyApp : public wxApp {
  public:
    bool OnInit() {
        wxInitAllImageHandlers();

#if DEBUG
        wxLog::SetActiveTarget(new AppLogger);
        wxLogMessage("Application Started");
#endif

        MainFrame *frame = new MainFrame();

        frame->Show(true);
        return true;
    }

    virtual int OnExit() {
        wxWakeUpIdle();
        return wxApp::OnExit();
    }
};

wxIMPLEMENT_APP(MyApp);
