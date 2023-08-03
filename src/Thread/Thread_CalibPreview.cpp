
#include "Event/Event_Error.hpp"
#include <Thread/Thread_CalibPreview.hpp>
#include <memory>
#include <opencv2/core/types.hpp>

CalibPreviewThread::CalibPreviewThread(wxEvtHandler *parent,
                                       std::unique_ptr<CameraBase> &camera,
                                       DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), camera(std::move(camera)), data(data) {
    this->parent = parent;

    auto config = AppConfig();
    auto previewConfig = config.GetPreviewConfig();
    int pWidth = previewConfig.width;
    int pHeight = previewConfig.height;
    this->pSize = cv::Size(pWidth, pHeight);

    auto cameraConfig = config.GetCameraConfig();
    int iWidth = cameraConfig.Camera_Width;
    int iHeight = cameraConfig.Camera_Height;
    this->imageSize = cv::Size(iWidth, iHeight);
}

CalibPreviewThread::~CalibPreviewThread() {}

wxThread::ExitCode CalibPreviewThread::Entry() {

    wxCommandEvent startCaptureEvent(c_CAPTURE_EVENT, CAPTURE_START);
    wxPostEvent(parent, startCaptureEvent);

    try {
        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                std::cout << "Failed to capture frame" << std::endl;
                continue;
            }

            cv::resize(frame, frame, pSize);

            auto isLineNull = data->calibData.isNull();
            if (!isLineNull) {
                auto calibData = data->calibData;
                cv::Scalar yellow(0, 255, 255);
                cv::Scalar blue(255, 0, 0);

                Detection::Line left = calibData.lineLeft;
                Detection::Line right = calibData.lineRight;

                left = left.Scale(imageSize, pSize);
                right = right.Scale(imageSize, pSize);

                cv::line(frame, left.p1, left.p2, yellow, 2);
                cv::line(frame, right.p1, right.p2, blue, 2);
            }

            UpdatePreviewEvent::Submit(parent, frame);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    wxCommandEvent endCaptureEvent(c_CAPTURE_EVENT, CAPTURE_END);
    wxPostEvent(parent, endCaptureEvent);

    return 0;
}

std::unique_ptr<CameraBase> CalibPreviewThread::getCamera() {
    return std::move(camera);
}

ThreadID CalibPreviewThread::getID() const { return id; }