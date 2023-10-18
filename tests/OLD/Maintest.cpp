#include "Model/CaptureModel.hpp"
#include "Model/SharedResource.hpp"
#include "Thread/Thread_Capture2.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <wx/gtk/window.h>
#include <wx/uiaction.h>
#include <wx/wx.h>

class LastEventCapture {
  public:
    LastEventCapture() : lastEvent(nullptr) {}

    void CaptureEvent(wxEvent &event) { lastEvent = &event; }

    wxEvent *GetLastEvent() const { return lastEvent; }

  private:
    wxEvent *lastEvent;
};

class TestFrame : public wxFrame {
    wxTextCtrl *textIn;
    wxButton *button;
    wxTextCtrl *textOut;
    // FRIEND_TEST(GuiTest, CopyTest);

  public:
    TestFrame()
        : wxFrame(NULL, wxID_ANY, "wxUnitTest", wxPoint(50, 50),
                  wxSize(450, 340)) {
        textIn = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                                wxDefaultPosition, wxDefaultSize, 0);
        button = new wxButton(this, wxID_ANY, wxT(" => "), wxDefaultPosition,
                              wxDefaultSize, 0);
        button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TestFrame::OnEvent, this);
        textOut = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                                 wxDefaultPosition, wxDefaultSize, 0);
        wxBoxSizer *boxSizer = new wxBoxSizer(wxHORIZONTAL);
        boxSizer->Add(textIn, 1, wxALL, 5);
        boxSizer->Add(button, 0, wxALL, 5);
        boxSizer->Add(textOut, 1, wxALL, 5);
        this->SetSizer(boxSizer);
        this->Layout();
        this->Centre(wxBOTH);
    }

    void OnButton(wxCommandEvent &WXUNUSED(event)) {
        this->textOut->SetValue(this->textIn->GetValue());
    }

    void OnEvent(wxEvent &evt) {
        // Capture the event
        throw std::runtime_error("not implemented");
        // Continue processing other events
        if (!evt.IsCommandEvent()) {
            evt.Skip();
        }
    }
};

class TestApp : public wxApp {
  public:
    TestFrame *frame;
    LastEventCapture lastEventCapture;

    virtual bool OnInit() {
        frame = new TestFrame();
        frame->Show(true);
        return true;
    }

    virtual int FilterEvent(wxEvent &event) {
        // Capture the event
        lastEventCapture.CaptureEvent(event);

        // Continue processing other events
        return wxApp::FilterEvent(event);
    }
};

class GuiTest : public testing::Test {
  protected:
    TestApp *app;
    virtual void SetUp() {
        char appname[] = "wxUnitTest.exe";
        int argc = 1;
        char *argv[1] = {appname};
        app = new TestApp();
        wxApp::SetInstance(app);
        wxEntryStart(argc, argv);
        app->OnInit();
    }
    virtual void TearDown() {
        //wxTheApp->OnRun();
        app->OnExit();
        wxEntryCleanup();
    }
};

// int main(int argc, char *argv[]) {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }

// TEST_F(GuiTest, CopyTest) {
//     wxUIActionSimulator acts;
//     app->frame->textIn->SetFocus();
//     wxYield();
//     acts.Text("Text");
//     wxYield();
//     app->frame->button->SetFocus();
//     wxYield();
//     acts.Char(WXK_RETURN);
//     wxYield();
//     ASSERT_EQ("Text", app->frame->textOut->GetValue());
// }

class MockCaptureModel : public CaptureModel {
  public:
    MOCK_METHOD1(stopAndDeleteThread, CaptureThread *(CaptureThread *thread));
    MOCK_METHOD1(stopAndDeleteThread, LoadFileThread *(LoadFileThread *thread));

    // Call the constructor of the base class
    MockCaptureModel(wxWindow *parent)
        : CaptureModel(std::make_shared<SharedModel>(parent)) {}

    void setCaptureThread(CaptureThread *thread) { captureThread = thread; }

    bool isCaptureThreadNull() { return captureThread == nullptr; }

    void setLoadFileThread(LoadFileThread *thread) { loadFileThread = thread; }

    bool isLoadFileThreadNull() { return loadFileThread == nullptr; }
};

class MockCaptureThread : public CaptureThread {
  public:
    MOCK_METHOD0(Entry, ExitCode());
    MockCaptureThread() : CaptureThread(wxTheApp->GetTopWindow(), nullptr) {}
};

class MockLoadFileThread : public LoadFileThread {
  public:
    MOCK_METHOD0(Entry, ExitCode());
    MockLoadFileThread() : LoadFileThread(nullptr, nullptr, nullptr, "", 0) {}
};

TEST_F(GuiTest, startLoadFileHandler_CaptureThreadNotNull) {
    // Create an instance of the mock CaptureModel
    MockCaptureModel model(wxTheApp->GetTopWindow());

    // Create a mock CaptureThread
    MockCaptureThread *mockCaptureThread = new MockCaptureThread();
    MockLoadFileThread *mockLoadFileThread = new MockLoadFileThread();
    ASSERT_TRUE(model.isCaptureThreadNull());

    model.setCaptureThread(mockCaptureThread);
    model.setLoadFileThread(mockLoadFileThread);

    EXPECT_FALSE(model.isLoadFileThreadNull());
    EXPECT_FALSE(model.isCaptureThreadNull());

    model.endPoint(app, ModelEnum::ModelIDs::MODEL_START_LOADFILE);
    //check event
    wxEvent *lastEvent = app->lastEventCapture.GetLastEvent();
    ASSERT_TRUE(lastEvent != nullptr);
    EXPECT_EQ(c_ERROR_EVENT, lastEvent->GetEventType());

    EXPECT_TRUE(model.isCaptureThreadNull());

    // // Cleanup
    // delete mockCaptureThread;
    // mockCaptureThread = nullptr;
}