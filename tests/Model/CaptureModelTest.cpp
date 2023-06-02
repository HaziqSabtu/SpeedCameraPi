#include "Model/CaptureModel.hpp"
#include "../testableframe.h"
#include "Event/Event_Error.hpp"
#include "Model/SessionData.hpp"
#include "Model/SharedModel.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_Capture2.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/DataStruct.hpp"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <opencv2/core/mat.hpp>
#include <wx/app.h>
#include <wx/event.h>
#include <wx/thread.h>
#include <wx/utils.h>
#include <wx/wx.h>

class CaptureModelTest : public testing::Test {
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

class MockCamera : public CameraBase {
  public:
    MockCamera(int w, int h) {
        this->width = w;
        this->height = h;

        this->fps = 30;

        this->frame = cv::Mat::zeros(height, width, CV_8UC3);
    }

    bool start() override { return true; }

    void stop() override { return; }

    void setResolution(int width, int height) override {
        this->width = width;
        this->height = height;
    }

    void setFPS(int fps) override { this->fps = fps; }

    void getFrame(cv::Mat &frame) override { frame = this->frame; }

    void setHeight(int height) override { this->height = height; }

    void setWidth(int width) override { this->width = width; }

    int width;
    int height;
    int fps;
    cv::Mat frame;
};

class MockCaptureThread : public wxThread {

  public:
    MockCaptureThread(wxEvtHandler *parent)
        : wxThread(wxTHREAD_JOINABLE), parent(parent) {}

  private:
    wxEvtHandler *parent;

    void sendPreviewUpdateEvent() {
        AppConfig config;
        CameraConfig cameraConfig = config.GetCameraConfig();
        int width = cameraConfig.Camera_Width;
        int height = cameraConfig.Camera_Height;

        cv::Mat frame = cv::Mat::zeros(height, width, CV_8UC3);

        UpdatePreviewEvent event(c_UPDATE_PREVIEW_EVENT, UPDATE_PREVIEW);
        event.SetImage(frame);
        wxPostEvent(parent, event);
    }

    virtual ExitCode Entry() override {
        sendPreviewUpdateEvent();
        return 0;
    }
};

class MockLoadFileThread : public wxThread {

  public:
    MockLoadFileThread(wxEvtHandler *parent)
        : wxThread(wxTHREAD_JOINABLE), parent(parent) {}

  private:
    wxEvtHandler *parent;

    virtual ExitCode Entry() override {
        wxCommandEvent startLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_START);
        wxPostEvent(parent, startLoadEvent);
        return 0;
    }
};

class MockLoadCaptureThread : public wxThread {

  public:
    MockLoadCaptureThread(wxEvtHandler *parent)
        : wxThread(wxTHREAD_JOINABLE), parent(parent) {}

  private:
    wxEvtHandler *parent;

    virtual ExitCode Entry() override {
        wxCommandEvent startLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_START);
        wxPostEvent(parent, startLoadEvent);
        return 0;
    }
};

class MockCaptureModel : public CaptureModel {
  public:
    MockCaptureModel(std::shared_ptr<SharedModel> shared)
        : CaptureModel(shared) {}

    wxThread *initCaptureThread(wxEvtHandler *parent,
                                std::shared_ptr<CameraBase> camera) override {
        return new MockCaptureThread(parent);
    }

    wxThread *initLoadFileThread(wxEvtHandler *parent, int maxFrame,
                                 std::string path) override {
        return new MockLoadFileThread(parent);
    }

    wxThread *
    initLoadCaptureThread(wxEvtHandler *parent,
                          std::shared_ptr<CameraBase> camera,
                          std::shared_ptr<std::vector<ImageData>> imgData,
                          const int maxFrame) override {
        return new MockLoadCaptureThread(parent);
    }

    MOCK_METHOD(bool, isRequirementFulfilled, (), (override));
};

TEST_F(CaptureModelTest, endPoint_PanelIDError) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();
    shared->sessionData.setPanelID(PANEL_ROI);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_CAPTURE);

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startCaptureHandler_cameraNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_CAPTURE);

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startCaptureHandler_captureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_CAPTURE);

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 0);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_CAPTURE);

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startCaptureHandlerOK) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_CAPTURE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, endCaptureHandler_captureThreadNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    wxYield();

    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_END_CAPTURE);

    counter.WaitEventNoSkip(1000, 0);
    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, endCaptureHandler_captureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_CAPTURE);

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_END_CAPTURE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(counter.GetCount() == oldCount);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, startLoadFileHandler_captureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_CAPTURE);

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADFILE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(counter.GetCount() == oldCount);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, startLoadFileHandler_loadFileThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADFILE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADFILE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startLoadFileHandler_imageDataNotEmpty) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    ImageData data(cv::Mat(100, 100, CV_8UC3, cv::Scalar(0, 0, 0)));
    std::vector<ImageData> vec = {data};
    shared->sessionData.imageData =
        std::make_shared<std::vector<ImageData>>(vec);

    int oldVecSize = shared->sessionData.imageData->size();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADFILE);

    counter.WaitEvent();
    ASSERT_TRUE(oldVecSize != shared->sessionData.imageData->size());
    ASSERT_TRUE(shared->sessionData.imageData->size() == 0);
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startLoadFileHandlerOK) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADFILE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, endLoadFileHandler_loadFileThreadNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    wxYield();

    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_END_LOADFILE);

    counter.WaitEventNoSkip(1000, 0);
    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, endLoadFileHandler_loadFileThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADFILE);

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_END_LOADFILE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(counter.GetCount() == oldCount);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, startLoadCaptureHandler_cameraNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADCAPTURE);

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startLoadCaptureHandler_captureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_CAPTURE);

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADCAPTURE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(counter.GetCount() == oldCount);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, startLoadCoptureHandler_loadCaptureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADCAPTURE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADCAPTURE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startLoadCaptureHandler_imageDataNotEmpty) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    ImageData data(cv::Mat(100, 100, CV_8UC3, cv::Scalar(0, 0, 0)));
    std::vector<ImageData> vec = {data};
    shared->sessionData.imageData =
        std::make_shared<std::vector<ImageData>>(vec);

    int oldVecSize = shared->sessionData.imageData->size();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADCAPTURE);

    counter.WaitEvent();
    ASSERT_TRUE(oldVecSize != shared->sessionData.imageData->size());
    ASSERT_TRUE(shared->sessionData.imageData->size() == 0);
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startLoadCaptureHandlerOK) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADCAPTURE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, endLoadCaptureHandler_loadCaptureThreadNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    wxYield();

    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_END_LOADCAPTURE);

    counter.WaitEventNoSkip(1000, 0);
    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, endLoadCaptureHandler_loadCaptureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    std::shared_ptr<MockCamera> camera = std::make_shared<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_START_LOADCAPTURE);

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_END_LOADCAPTURE);

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(counter.GetCount() == oldCount);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, switchPanelHandler_requirementFalse) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_CHANGE_PANEL_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    EXPECT_CALL(model, isRequirementFulfilled())
        .WillOnce(::testing::Return(false));

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_SWITCH_PANEL);

    counter.WaitEventNoSkip(1000, 0);

    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 1);
}

TEST_F(CaptureModelTest, switchPanelHandler_requirementTrue) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_CHANGE_PANEL_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    EXPECT_CALL(model, isRequirementFulfilled())
        .WillOnce(::testing::Return(true));

    model.endPoint(wxTheApp->GetTopWindow(),
                   ModelEnum::ModelIDs::MODEL_SWITCH_PANEL);

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}