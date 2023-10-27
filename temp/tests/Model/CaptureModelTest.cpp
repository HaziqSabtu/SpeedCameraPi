#include "../testableframe.h"
#include "Controller/CaptureController.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_LoadImage.hpp"
#include "Model/SessionData.hpp"
#include "Model/SharedResource.hpp"
#include "Thread/Thread_CameraPreview.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
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
        wxCommandEvent startLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_START_FILE);
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
        wxCommandEvent startLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_START_CAMERA);
        wxPostEvent(parent, startLoadEvent);
        return 0;
    }
};

class MockCaptureModel : public CaptureController {
  public:
    MockCaptureModel(std::shared_ptr<SharedModel> shared)
        : CaptureController(shared) {}

    MockCaptureThread *initCaptureThread(wxEvtHandler *parent,
                                         std::shared_ptr<CameraBase> camera) {
        return new MockCaptureThread(parent);
    }

    wxThread *initLoadFileThread(wxEvtHandler *parent, int maxFrame,
                                 std::string path) {
        return new MockLoadFileThread(parent);
    }

    wxThread *
    initLoadCaptureThread(wxEvtHandler *parent, CameraPtr camera,
                          std::shared_ptr<std::vector<ImageData>> imgData,
                          const int maxFrame) {
        return new MockLoadCaptureThread(parent);
    }

    //MOCK_METHOD(bool, isRequirementFulfilled, (), (override));
};

TEST_F(CaptureModelTest, endPoint_PanelIDError) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();
    shared->sessionData.setPanelID(PANEL_ROI);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_CameraStart(wxTheApp->GetTopWindow());

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startCaptureHandler_cameraNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_CameraStart(wxTheApp->GetTopWindow());

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startCaptureHandler_captureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_CameraStart(wxTheApp->GetTopWindow());

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 0);

    model.e_CameraStart(wxTheApp->GetTopWindow());

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startCaptureHandlerOK) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);

    model.e_CameraStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, endCaptureHandler_captureThreadNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    wxYield();

    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    model.e_LoadCaptureEnd(wxTheApp->GetTopWindow());

    counter.WaitEventNoSkip(1000, 0);
    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, endCaptureHandler_captureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_CameraStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.e_LoadCaptureEnd(wxTheApp->GetTopWindow());

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(counter.GetCount() == oldCount);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, startLoadFileHandler_captureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_CameraStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.e_LoadFileStart(wxTheApp->GetTopWindow(), "std::string path");

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

    model.e_LoadFileStart(wxTheApp->GetTopWindow(), "std::string path");

    model.e_LoadFileStart(wxTheApp->GetTopWindow(), "std::string path");

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    model.e_LoadFileStart(wxTheApp->GetTopWindow(), "std::string path");

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

    model.e_LoadFileStart(wxTheApp->GetTopWindow(), "std::string path");

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

    model.e_LoadFileStart(wxTheApp->GetTopWindow(), "std::string path");

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

    model.e_LoadFileEnd(wxTheApp->GetTopWindow());

    counter.WaitEventNoSkip(1000, 0);
    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, endLoadFileHandler_loadFileThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_LoadFileStart(wxTheApp->GetTopWindow(), "std::string path");

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.e_LoadFileEnd(wxTheApp->GetTopWindow());

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(counter.GetCount() == oldCount);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, startLoadCaptureHandler_cameraNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_LoadCaptureStart(wxTheApp->GetTopWindow());

    wxYield();
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startLoadCaptureHandler_captureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_UPDATE_PREVIEW_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_CameraStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.e_LoadCaptureStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() > 0);
    ASSERT_TRUE(counter.GetCount() == oldCount);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, startLoadCoptureHandler_loadCaptureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_LoadCaptureStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    model.e_LoadCaptureStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startLoadCaptureHandler_imageDataNotEmpty) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    ImageData data(cv::Mat(100, 100, CV_8UC3, cv::Scalar(0, 0, 0)));
    std::vector<ImageData> vec = {data};
    shared->sessionData.imageData =
        std::make_shared<std::vector<ImageData>>(vec);

    int oldVecSize = shared->sessionData.imageData->size();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);

    model.e_LoadCaptureStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();
    ASSERT_TRUE(oldVecSize != shared->sessionData.imageData->size());
    ASSERT_TRUE(shared->sessionData.imageData->size() == 0);
    ASSERT_TRUE(counter.GetCount() == 1);
}

TEST_F(CaptureModelTest, startLoadCaptureHandlerOK) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_LoadCaptureStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();
    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, endLoadCaptureHandler_loadCaptureThreadNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    wxYield();

    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    model.e_LoadCaptureEnd(wxTheApp->GetTopWindow());

    counter.WaitEventNoSkip(1000, 0);
    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}

TEST_F(CaptureModelTest, endLoadCaptureHandler_loadCaptureThreadNotNull) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    CameraPtr camera = std::make_unique<MockCamera>(100, 100);
    shared->setCamera(camera);

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_LOAD_IMAGE_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    model.e_LoadCaptureStart(wxTheApp->GetTopWindow());

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);

    int oldCount = counter.GetCount();

    model.e_LoadCaptureEnd(wxTheApp->GetTopWindow());

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

    // !Caution: Check if this is correct
    // EXPECT_CALL(model, isRequirementFulfilled())
    //     .WillOnce(::testing::Return(false));

    // model.endPoint(wxTheApp->GetTopWindow(),
    //                ModelEnum::ModelIDs::MODEL_SWITCH_PANEL);

    counter.WaitEventNoSkip(1000, 0);

    ASSERT_TRUE(counter.GetCount() == 0);
    ASSERT_TRUE(errorCounter.GetCount() == 1);
}

TEST_F(CaptureModelTest, switchPanelHandler_requirementTrue) {
    std::shared_ptr<SharedModel> shared = std::make_shared<SharedModel>();

    MockCaptureModel model(shared);

    EventCounter counter(wxTheApp->GetTopWindow(), c_CHANGE_PANEL_EVENT);
    EventCounter errorCounter(wxTheApp->GetTopWindow(), c_ERROR_EVENT);

    // !Caution: Check if this is correct
    // EXPECT_CALL(model, isRequirementFulfilled())
    //     .WillOnce(::testing::Return(true));

    // model.endPoint(wxTheApp->GetTopWindow(),
    //                ModelEnum::ModelIDs::MODEL_SWITCH_PANEL);

    counter.WaitEvent();

    ASSERT_TRUE(counter.GetCount() == 1);
    ASSERT_TRUE(errorCounter.GetCount() == 0);
}