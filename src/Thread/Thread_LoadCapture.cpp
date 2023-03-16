#include <Thread/Thread_LoadCapture.hpp>

LoadCaptureThread::LoadCaptureThread(wxEvtHandler *parent,
                                     raspicam::RaspiCam_Cv *camera,
                                     const int maxFrame, const bool debug)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), camera(camera),
      maxFrame(maxFrame), debug(debug) {}

LoadCaptureThread::~LoadCaptureThread() { camera = nullptr; }

wxThread::ExitCode LoadCaptureThread::Entry() {
    if (!camera->isOpened()) {
        std::cout << "Failed to open camera" << std::endl;
        return 0;
    }

    std::unique_ptr<std::vector<ImageData>> imgData =
        std::make_unique<std::vector<ImageData>>();

    CaptureImageEvent startCaptureEvent(c_CAPTURE_IMAGE_EVENT, CAPTURE_START);
    wxPostEvent(parent, startCaptureEvent);

    cv::Mat frame;

    for (int i = 0; i < maxFrame; i++) {
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
    }

    cv::Mat first = imgData->at(0).image;
    UpdateImageEvent updateImageEvent(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
    updateImageEvent.SetImageData(first);
    wxPostEvent(parent, updateImageEvent);

    if (debug) {
        FILEWR::WriteFile(imgData.get());
    }

    CaptureImageEvent stopCaptureEvent(c_CAPTURE_IMAGE_EVENT, CAPTURE_END);
    stopCaptureEvent.SetImageData(imgData.release());
    wxPostEvent(parent, stopCaptureEvent);

    return 0;
}