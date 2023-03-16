#include <Thread/Thread_LoadCapture.hpp>

LoadCaptureThread::LoadCaptureThread(wxEvtHandler *parent,
                                     raspicam::RaspiCam_Cv *camera)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), camera(camera) {}

LoadCaptureThread::~LoadCaptureThread() { camera = nullptr; }

wxThread::ExitCode LoadCaptureThread::Entry() {
    if (!camera->isOpened()) {
        std::cout << "Failed to open camera" << std::endl;
        return 0;
    }

    AppConfig *appConfig = new AppConfig();
    CaptureConfig captureConfig = appConfig->GetCaptureConfig();

    std::unique_ptr<std::vector<ImageData>> imgData =
        std::make_unique<std::vector<ImageData>>();

    CaptureImageEvent startCaptureEvent(c_CAPTURE_IMAGE_EVENT, CAPTURE_START);
    wxPostEvent(parent, startCaptureEvent);

    cv::Mat frame;
    const int MAX = captureConfig.Max_Frame_Count;
    const int INTERVAL = captureConfig.Frame_Interval;

    for (int i = 0; i < MAX; i++) {
        camera->grab();
        camera->retrieve(frame);
        if (frame.empty()) {
            std::cout << "Failed to capture frame" << std::endl;
            continue;
        }
        imgData->push_back(ImageData(frame.clone()));
        UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
        event.SetImageData(ImageData(frame));
        wxPostEvent(parent, event);

        if (TestDestroy()) {
            break;
        }
        // wxMilliSleep(INTERVAL);
    }

    cv::Mat first = imgData->at(0).image;
    UpdateImageEvent updateImageEvent(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
    updateImageEvent.SetImageData(first);
    wxPostEvent(parent, updateImageEvent);

    bool debug = true;
    if (debug) {
        FILEWR::WriteFile(imgData.get());
    }

    CaptureImageEvent stopCaptureEvent(c_CAPTURE_IMAGE_EVENT, CAPTURE_END);
    stopCaptureEvent.SetImageData(imgData.release());
    wxPostEvent(parent, stopCaptureEvent);

    delete appConfig;
    appConfig = nullptr;

    return 0;
}