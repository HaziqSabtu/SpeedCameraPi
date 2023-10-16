#include "Model/CaptureModel.hpp"
#include "Thread/Thread_Capture2.hpp"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <wx/app.h>

using namespace testing;

// MockEvtHandler class
class MockEvtHandler : public wxEvtHandler {
  public:
    // Method to access the last executed event
    const wxEvent *getLastEvent() const { return lastEvent; }

  private:
    const wxEvent *lastEvent = nullptr;

    // Override ProcessEvent to store the last executed event
    bool ProcessEvent(wxEvent &event) override {
        lastEvent = &event;
        return wxEvtHandler::ProcessEvent(event);
    }
};

// Mock class for the CaptureModel class
class MockCaptureModel : public CaptureModel {
  public:
    MOCK_METHOD1(stopAndDeleteThread, CaptureThread *(CaptureThread *thread));
    MOCK_METHOD1(stopAndDeleteThread, LoadFileThread *(LoadFileThread *thread));

    // Call the constructor of the base class
    MockCaptureModel() : CaptureModel(nullptr) {}

    void setCaptureThread(CaptureThread *thread) { captureThread = thread; }

    bool isCaptureThreadNull() { return captureThread == nullptr; }

    void setLoadFileThread(LoadFileThread *thread) { loadFileThread = thread; }

    bool isLoadFileThreadNull() { return loadFileThread == nullptr; }
};

class MockCaptureThread : public CaptureThread {
  public:
    MOCK_METHOD0(Entry, ExitCode());
    MockCaptureThread() : CaptureThread(wxTheApp->GetTopWindow(), nullptr) {}
    // : CaptureThread2(new wxFrame(nullptr, wxID_ANY, "Test")) {}
};

class MockLoadFileThread : public LoadFileThread {
  public:
    MOCK_METHOD0(Entry, ExitCode());
    MockLoadFileThread() : LoadFileThread(nullptr, nullptr, nullptr, "", 0) {}
    // MockLoadFileThread() : LoadFileThread(nullptr, nullptr, nullptr, "", 0) {}
};

// Test case for the endPoint method
TEST(CaptureModelTest, startLoadFileHandler_CaptureThreadNotNull) {
    // Create an instance of the mock CaptureModel
    MockCaptureModel model;

    // Create a mock CaptureThread
    MockCaptureThread mockCaptureThread;

    // // Set the captureThread to the mockCaptureThread
    model.setCaptureThread(&mockCaptureThread);

    // model.endPoint(nullptr, ModelEnum::ModelIDs::MODEL_START_LOADFILE);

    // // Expect that stopAndDeleteThread is called with the mockCaptureThread
    // EXPECT_CALL(model, stopAndDeleteThread(mockCaptureThread))
    //     .WillOnce(::testing::Return(nullptr));

    // ASSERT_TRUE(model.isCaptureThreadNull());

    // // Cleanup
    // delete mockCaptureThread;
    // mockCaptureThread = nullptr;
}

TEST(CaptureModelTest, startLoadFileHandler_LoadThreadNotNull) {
    // Create an instance of the mock CaptureModel
    MockCaptureModel model;

    // Create a mock LoadFileThread
    MockLoadFileThread *mockLoadFileThread = new MockLoadFileThread();

    // Set the loadFileThread to the mockLoadFileThread
    model.setLoadFileThread(mockLoadFileThread);

    ASSERT_THROW(model.endPoint(wxTheApp->GetTopWindow(),
                                ModelEnum::ModelIDs::MODEL_START_LOADFILE),
                 std::exception);
}